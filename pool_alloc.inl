// dumb global-state thread-unsafe allocator
// do not reuse!

static constexpr size_t PAGE_SIZE = 1024*1024;
std::vector<std::vector<uint8_t>> g_pool(1);

template <typename T>
class pool_alloc
{
public:    
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_swap;
    static constexpr size_t elem_size = sizeof(T);

    pool_alloc()
    {
    }

    ~pool_alloc()
    {
    }

    pool_alloc(const pool_alloc& other)
    {
    }

    template <typename Other>
    pool_alloc(const pool_alloc<Other>& other)
    {
    }

    pointer allocate(size_type size, const void* = nullptr)
    {
        size *= elem_size;

        if (g_pool.back().size() + size > PAGE_SIZE)
        {
            g_pool.emplace_back();
        }

        if (g_pool.back().capacity() == 0)
        {
            g_pool.back().reserve(std::max(PAGE_SIZE, size));
        }

        auto os = g_pool.back().size();
        g_pool.back().resize(g_pool.back().size() + size);
        return reinterpret_cast<pointer>(g_pool.back().data() + os);
    }

    void deallocate(pointer mem, size_type)
    {
        // we no care
    }

    size_type max_size() const
    {
        return 2000000000; // whatever
    }

    pool_alloc& operator=(const pool_alloc& other)
    {
        return *this;
    }

    template <class Other>
    pool_alloc& operator=(const pool_alloc<Other>& other)
    {
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // boilerplate follows
    template <typename Other>
    struct rebind { typedef pool_alloc<Other> other; };

    pointer address(reference ref) const
    {
        return &ref;
    }

    const_pointer address(const_reference ref) const
    {
        return &ref;
    }

    void construct(pointer ptr, const value_type& val)
    {
        ::new(ptr)value_type(val);
    }

    void destroy(pointer ptr)
    {
        ptr->~value_type();
    }
};

template <typename T, typename Pool>
bool operator ==(const pool_alloc<T>& a, const pool_alloc<T>& b)
{
    return true;
}

template <typename T, typename Pool>
bool operator !=(const pool_alloc<T>& a, const pool_alloc<T>& b)
{
    return !false;
}

struct pool_aloc_scope
{
    ~pool_aloc_scope()
    {
        g_pool.resize(1);
        g_pool.back().clear();
    }
};