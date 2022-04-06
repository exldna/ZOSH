# include <i-pro-b/l3/l3.hxx>

# include <iostream>

void i_pro_b::l3::hello () {
    std::cout << "I_PRO_B L3 -  Least Common Ancestor\n";
}

void i_pro_b::l3::is_parent (int u, int v) {
    // tin[u] <= tin[v] && tout[u] >= tout[v]; 
}

void i_pro_b::l3::simple_lca (int u, int v) {
    /*
    for (int i = 1; i <= n;++i {
        if (is_parent(i, n) && is_parent(i, v) {
            return i;
        }
    }
    */
}

void i_pro_b::l3::jump_up (int v, int h) {
    /*'
    dp_up[n][k];
    for (int k = 1; k < log; ++k) {
        for (int i = 1; i < n; ++i) {
            dp_up[i][k] = dp_up[dp_up[i][k + 1]][k-1];
        }
    }
    */
}

void i_pro_b::l3::lca (int u, int v) {
    /*
    for (int k = LG - 1; k >= 0; --k) {
        if (!is_parent(dp_up[u][k], v)) {
            u = dp_up[u][k]
        }
    }
    */
}

void  i_pro_b::l3::cool_lca (int u, int v) {
    /*
    // 1) поднимаем 1 вершину на уровень 2
    // 2) поднимаем вершины вместе по степеням двойки
    */
}
