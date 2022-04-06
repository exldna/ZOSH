# ifndef I_PRO_B_L5_HXX
# define I_PRO_B_L5_HXX

# include <vector>
# include <optional>
# include <random>

namespace i_pro_b::l5 {

    void hello ();



    template <typename _Key = size_t> 
    class Treap {

    public:

        struct item;
        using p_item = item*;

    public:

        explicit Treap () noexcept
            : root (nullptr), sz (0), rnd()
        {}

        explicit Treap (const std::vector<_Key>& base) noexcept 
            : root (nullptr), sz (0), rnd() {
            for (auto& el : base) insert (el);
        }

        ~Treap () {
            _deliter (root);
        }

        Treap (const Treap& other)
            : root (nullptr), sz (0) 
        {
            _copyer (other.root);
        }

        Treap* operator= (const Treap& other) {
            _copyer (other.root);
        }

        Treap (Treap&& other) {
            root = std::move(other.root);
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }

        Treap& operator= (Treap&&) {
            root = std::move (other.root);
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }

        void insert (const _Key& key) {
            if (!search (key)) {
                auto new_item = new item (key, rnd (10000));
                _insert (root, new_item);
                std::cout << "insert\n";
                ++sz;
            }
        }

        void erase (const _Key& key) {
            if (search (key)) {
                _erase (root, key);
                --sz;
            }
        }

        bool search (const _Key& key) {
            return _search (key, root) != nullptr;
        }

        const _Key& k_ord_stat () {

        }

        size_t size () {
            return sz;
        }

    // private:

        struct item {
            p_item ch_l, ch_r;
            size_t prior;
            _Key key;

            item (const _Key& _key, size_t _prior)
                : ch_l (nullptr), ch_r (nullptr)
            {
                key = std::move(_key);
                prior = _prior;
            }
        };

        struct rand {
            std::mt19937_64 engine {};

            rand () {
                std::random_device device;
                engine.seed (device ());
            }

            size_t operator() (size_t max_range) {
                std::uniform_int_distribution<size_t> dist (0, max_range);
                return dist (engine);
            }
        };

        p_item root;
        size_t sz;
        rand rnd;

        static void _deliter (p_item& i) {
            if (i == nullptr) return;
            if (i->ch_l != nullptr) _deliter (i->ch_l);
            if (i->ch_r != nullptr) _deliter (i->ch_r);
            delete i;
            i = nullptr;
        }

        void _copyer (const p_item& i) {
            if (i == nullptr) return;
            insert (i->key);
            _copyer (i->ch_l);
            _copyer (i->ch_r);
        };

        static void _insert (p_item& t, p_item it) {
            if (t == nullptr) t = it;
            else if (it->prior > t->prior) {
                _split (t, it->key, it->ch_l, it->ch_r);
                t = it;
            } else {
                if (it->key < t->key) {
                    _insert (t->ch_l, it);
                } else {
                    _insert (t->ch_r, it);
                }
            }
        }

        static void _erase (p_item& t, const _Key& key) {
            if (t == nullptr) return;
            else if (t->key == key)
                p_item tmp = t;
                _merge (t, t->ch_l, t->ch_r);
                delete tmp;
            else {
                _erase ((key < t->key ? t->ch_l : t->ch_r), key);
            }
        }

        static p_item _search (const _Key& key, const p_item& t) {
            if (t == nullptr) return nullptr;
            if (key == t->key) return t;
            else if (key > t->key) return _search (key, t->ch_r);
            else if (key < t->key) return _search (key, t->ch_l);
            return nullptr;
        }

        static void _split (const p_item& t, const _Key& key, p_item& tl, p_item& tr) {
            if (t == nullptr) {
                tl = nullptr;
                tr = nullptr;
            } else if (key < t->key) {
                _split (t->ch_l, key, tl, t->ch_l);
                tr = t;
            } else {
                _split (t->ch_r, key, t->ch_r, tr);
                tl = t;
            }
        }

        static void _merge (p_item& t, const p_item& tl, const p_item& tr) {
            if (tl == nullptr && tr == nullptr)
                t = nullptr;
            else if (tl == nullptr || tr == nullptr) 
                t = (tl == nullptr ? tr : tl);
            else if (tl->prior > tr->prior) {
                _merge (tl->ch_r, tl->ch_r, tr); 
                t = tl;
            } else {
                _merge (tr->ch_l, tl, tr->ch_l);
                t = tr;
            }
        }
        
    };

}

# endif // !I_PRO_B_L5_HXX