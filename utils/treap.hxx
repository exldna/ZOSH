# ifndef _TREAP_HXX
# define _TREAP_HXX

# include <utils/pool.hxx>
# include <vector>

template <typename _Key, template <class> typename _Alloc = PoolAllocator>
class Treap {
public:

private:

    struct Node {

    };

    _Alloc<_Key> keys_buffer;
    _Alloc<Node> nodes_buffer;

};

# endif // !_TREAP_HXX