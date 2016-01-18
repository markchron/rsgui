#ifndef ENVSET
#define ENVSET

//int const ENV_INFINITE_SIZE = 128;

typedef enum {
    ENV_SIM_BLACK_OIL,
    ENV_SIM_COMPOSITION,
    ENV_SIM_THERMAL
} envsimtype_et;

typedef enum {
    ENV_UNIT_UNDEFINED = -1,
    ENV_UNIT_SI,
    ENV_UNIT_FIELD
} envunittype_et;

typedef enum{
    ENV_POROSITY_UNDEFINED = -1,
    ENV_POROSITY_SINGLE,
    ENV_POROSITY_DUAL_POROSITY,
    ENV_POROSITY_DUAL_PERM,
    ENV_POROSITY_DUAL_POR_DUAL_PERM
} envporositytype_et;

typedef enum {
    ENV_GRID_TYPE_CART,
    ENV_GRID_TYPE_CYLINDRAL,
    ENV_GRID_TYPE_CORNER
} envgridtype_et;

typedef enum {
    ENV_GRID_KDIR_UP,
    ENV_GRID_KDIR_DOWN
} envgridkdir_et;

#endif // ENVSET

