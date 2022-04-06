# ifndef _POOL_ALLOC_HXX
# define _POOL_ALLOC_HXX

# include <cstddef>
# include <memory>

template <typename _Type, std::size_t pg_size = 100>
class PoolAllocator {
public:

    PoolAllocator ();
    ~PoolAllocator ();

    PoolAllocator (const PoolAllocator&);
    PoolAllocator& operator= (const PoolAllocator&);
    PoolAllocator (PoolAllocator&&);
    PoolAllocator& operator= (PoolAllocator&&);

    _Type* allocate (std::size_t n);
    void deallocate (_Type* p, std::size_t n);

private:

    struct Page {
        struct Node {
            std::unique_ptr<Node> next_nd;
            _Type object;
        };

        std::unique_ptr<Page> next_pg;
        std::unique_ptr<Node> nodes;

        Page ();
        ~Page ();

        Page (const Page&) = delete;
        Page& operator= (const Page&) = delete;
        Page (Page&&) = delete;
        Page& operator= (Page&&) = delete;

        Node& operator[] (std::size_t i);

        void insert (const _Type& object);
        void insert (_Type&& object);

        template <typename ..._Args>
        void emplace (_Args&&... args);
    };

    std::unique_ptr<void> buffer;

};

# endif // !_POOL_ALLOC_HXX