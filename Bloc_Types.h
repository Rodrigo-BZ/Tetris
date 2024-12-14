#include <iostream>
#include "Blocs.h"

class BlocL: public Bloc{
public:
    BlocL(): Bloc(){
        forme = {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        }};
        color = QColor(255,165,0); //orange
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
        color = QColor(0,255,255); //cyan
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
        color = QColor(255,255,0); //yellow
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
        color = QColor(128,0,128); //purple
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
        color = QColor(0,0,255); //blue
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
        color = QColor(0,255,0); //green
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
        color = QColor(255,0,0); //red
    }
};
