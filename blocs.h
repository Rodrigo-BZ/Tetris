#include <iostream>
#include "class_bloc.hpp"

class L: public Bloc{
    public: 
    L(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
}

class I: public Bloc{
    public: 
    I(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }};
    }
}

class O: public Bloc{
    public: 
    O(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
}

class T: public Bloc{
    public: 
    T(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
}

class J: public Bloc{
    public: 
    J(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
}

class S: public Bloc{
    public: 
    S(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
}

class Z: public Bloc{
    public: 
    Z(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
}
