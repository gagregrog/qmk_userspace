#include "gagregrog.h"

void td_handle_L1_K1(TD_ARGS_GAGREGROG);
void td_handle_L1_K2(TD_ARGS_GAGREGROG);
void td_handle_L2_K2(TD_ARGS_GAGREGROG);

enum tap_dance_keys {
  T_L1_K1,
  T_L1_K2,
  T_L2_K2,
};

#define TD_L1_K1 TD(T_L1_K1)
#define TD_L1_K2 TD(T_L1_K2)
#define TD_L2_K2 TD(T_L2_K2)
