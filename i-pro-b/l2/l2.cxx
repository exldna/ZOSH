# include <i-pro-b/l2/l2.hxx>

# include <iostream>

void i_pro_b::l2::hello () {
    std::cout << "I_PRO_B L2 - DKA\n";
}

void i_pro_b::l2::build_comments () {
    /*
    * 1.
    p = [s]
    while (p != -1 && p.to[c] == -1) {
        p.to[c] = cur // cur = [Sc]
        p = p.link
    }
    * 2.
    if (p == -1) {
        cur.link = root
    }
    * 3.
    if (p != -1) {
        if (len(q) == len(p + 1)) {
            cur.link = q
        } else { // if len(q) > len(p) + 1
             // clone
        }
    }
    */
}
