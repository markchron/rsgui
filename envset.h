#ifndef ENVSET
#define ENVSET

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

#endif // ENVSET

