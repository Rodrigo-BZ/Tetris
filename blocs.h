#include <iostream>
#include "class_bloc.h"

class BlocL: public Bloc{
    public: 
    BlocL(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
};

class BlocI: public Bloc{
    public: 
    BlocI(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }};
    }
};

class BlocO: public Bloc{
    public: 
    BlocO(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
};

class BlocT: public Bloc{
    public: 
    BlocT(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
};

class BlocJ: public Bloc{
    public: 
    BlocJ(int c, int k): Bloc(c,k){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
};

class BlocS: public Bloc{
    public: 
    BlocS(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }};
    }
};

class BlocZ: public Bloc{
    public: 
    BlocZ(int c, int k): Bloc(c,k){
        forme = {{
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
    }
};
