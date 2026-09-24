#include<stdint.h>



typedef struct bit_range {
  uint8_t width;
  uint8_t offset;
} bit_range;

constexpr bit_range OP 	= {.width = 7u, .offset = 0 };
constexpr bit_range RD 	= {.width = 5u, .offset = 7 };
constexpr bit_range F3 	= {.width = 3u, .offset = 12};
constexpr bit_range RS1 = {.width = 5u, .offset = 15};
constexpr bit_range RS2	= {.width = 5u, .offset = 20};
constexpr bit_range F7  = {.width = 7u, .offset = 25};
constexpr bit_range F7BIT5 = {.width = 1u, .offset = 30};
constexpr bit_range I_IMM = {.width = 12, .offset = 20};

[[gnu::always_inline]] static inline uint32_t getf (bit_range field, uint32_t instr) {
  return (instr >> field.offset) & ((1 << field.width) - 1u);
}

[[gnu::always_inline]] static inline uint32_t dec_imm_i (uint32_t instr) {
  return getf(I_IMM, instr);
}


typedef uint32_t (*op_handler) (uint32_t instr);

uint32_t handler_0x33 (uint32_t instr) {
  return 0;
}

uint32_t handler_0x13 (uint32_t instr) {
  return 0;
}

op_handler dec_tab [256u] = {
  [0x33] = handler_0x33,
  [0x13] = handler_0x13
};
