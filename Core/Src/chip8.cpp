#include "chip8.h"
#include <vector>

uint8_t fontset[FONTSET_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() {}

Chip8::~Chip8() {}

void Chip8::init(void) {
  program_counter =
      0x200; // programs loadesd into memory starting at address 0x200
  sp = 0;
  I = 0;
  delay_timer = 0;
  sound_timer = 0;
  op = 0;
  jump_flag = false;
  draw_flag = false;

  int i = 0;
  for (i; i < RAM_SIZE; i++) {
    mem[i] = 0;
  }

  CLEAR_SCR();

  for (i = 0; i < GREG_SIZE; i++) {
    V[i] = 0;
    stack[i] = 0;
    keypad[i] = 0;
  }

  for (int i = 0; i < FONTSET_SIZE; i++) {
    mem[i] = fontset[i];
  }
}
bool Chip8::load(char *filename) {
  // load file bytes into mem and start filling mem from location 0x200
  std::FILE *game = std::fopen(filename, "rb");
  if (game == nullptr) {
    std::cerr << "Error opening file : " << filename << std::endl;
    return false;
  }
  // get file size
  std::fseek(game, 0, SEEK_END);
  auto fileSize = std::ftell(game);
  std::fseek(game, 0, SEEK_SET);

  // check if file size will not overflow emulated memory size
  if (fileSize > ROM_SIZE) {
    std::cerr << "File too big" << std::endl;
    std::fclose(game);
    return false;
  }

  std::fread(&mem[0x200], 1, fileSize, game);
  std::fclose(game);
  std::cout << "Successfully loaded : " << filename << std::endl;
  return true;
}
void Chip8::emulate(void) {
  jump_flag = false;
  draw_flag = false;
  fetch();
  cout << "opcode : " << std::hex << op << std::endl;
  execute();

  if (!jump_flag) {
    incPC();
  }

  if (delay_timer > 0) {
    delay_timer--;
  }
  if (sound_timer > 0) {
    if (sound_timer == 1) {
      // sound lib
    }
    sound_timer--;
  }
  key_flag = false;
}

void Chip8::RET() {
  sp--;
  program_counter = stack[sp];
  stack[sp] = 0;
}

void Chip8::CLEAR_SCR() {
  for (int i = 0; i < DISP_SIZE; i++) {
    display[i] = 0;
  }
  draw_flag = true;
}
uint8_t Chip8::get_x() { return (op & 0x0F00) >> 8; }
uint8_t Chip8::get_y() { return (op & 0x00F0) >> 4; }
uint8_t Chip8::get_nn() { return (op & 0x00FF); }
void Chip8::JUMP(void) {
  program_counter = op & 0x0FFF;
  jump_flag = true;
}
void Chip8::CALL(void) {
  stack[sp] = program_counter;
  sp++;
  JUMP();
}
void Chip8::SKIP_FEQ(void) {
  if (V[get_x()] == get_nn()) {
    incPC();
  }
}
void Chip8::SKIP_NEQ(void) {
  if (V[get_x()] != get_nn()) {
    incPC();
  }
}
void Chip8::SKIP_YXEQ(void) {
  if (V[get_x()] == V[get_y()]) {
    incPC();
  }
}
void Chip8::MOV_X(void) { V[get_x()] = get_nn(); }
void Chip8::ADD_X(void) { V[get_x()] += get_nn(); }

void Chip8::MOV_YX(void) { V[get_x()] = V[get_y()]; }
void Chip8::OR_X(void) { V[get_x()] |= V[get_y()]; }
void Chip8::AND_X(void) { V[get_x()] &= V[get_y()]; }
void Chip8::XOR_X(void) { V[get_x()] ^= V[get_y()]; }
void Chip8::ADDC_YX(void) {
  if (V[get_y()] > (0xFF - V[get_x()])) {
    V[0xF] = 0x1;
  } else {
    V[0xF] = 0x0;
  }
  V[get_x()] += V[get_y()];
}
void Chip8::SUBBOR_YX(void) {
  if (V[get_x()] >= V[get_y()]) {
    V[0xF] = 0x1;
  } else {
    V[0xF] = 0x0;
  }
  V[get_x()] -= V[get_y()];
}
void Chip8::SHIFTR(void) {
  V[0xF] = 0x01 & V[get_x()];
  V[get_x()] >>= 1;
}
void Chip8::SUB_X(void) {
  if (V[get_y()] >= V[get_x()]) {
    V[0xF] = 0x1;
  } else {
    V[0xF] = 0x0;
  }
  V[get_x()] = V[get_y()] - V[get_x()];
}
void Chip8::SHIFTL(void) {
  V[0xF] = (V[get_x()] >> 7) & 0x1;
  V[get_x()] <<= 1;
}

void Chip8::SKIP_YXNEQ(void) {
  if (V[get_x()] != V[get_y()]) {
    incPC();
  }
}
void Chip8::STR_ADDR(void) { I = op & 0x0FFF; }
void Chip8::JUMP_V0(void) {
  JUMP();
  program_counter += V[0];
}
void Chip8::RAND(void) { V[get_x()] = (rand() % 255) & get_nn(); }
// FIXME
void Chip8::DRAW(void) {
  uint8_t y = V[get_y()];
  uint8_t x = V[get_x()];
  uint8_t n = op & 0x000F;
  uint8_t byte = 0;
  uint8_t bit = 0;
  uint8_t temp;
  int location;
  V[0xF] = 0x0;
  // starting from (x,y) on display
  // draw n bytes from location I in mem

  for (uint8_t i = 0; i < n; i++) {
    byte = mem[I + i];
    location = (y + i) * DISP_WIDTH + x;
    // need draw and check xor on each bit
    for (uint8_t z = 0; z < 8; z++) {
      temp = display[(location + z) % DISP_SIZE] ^ (byte >> (7 - z)) & 0x01;
      if (display[(location + z) % DISP_SIZE] && !temp) {
        V[0xF] = 0x1;
      }
      display[(location + z) % DISP_SIZE] = temp;
    }
  }
  draw_flag = true;
}

void Chip8::SKIP_PRESS(void) {
  if (keypad[V[get_x()]] == 1) {
    incPC();
  }
}
void Chip8::SKIP_NPRESS(void) {
  if (keypad[V[get_x()]] == 0) {
    incPC();
  }
}

void Chip8::STR_DEL(void) { V[get_x()] = delay_timer; }
void Chip8::WAIT_KEY(void) {
  jump_flag = true;
  if (key_flag) {
    V[get_x()] = key_index;
    jump_flag = false;
  }
}
void Chip8::SET_DEL(void) { delay_timer = V[get_x()]; }
void Chip8::SET_SND(void) { sound_timer = V[get_x()]; }
void Chip8::ADD_I(void) {
  I += V[get_x()];
  if (V[get_x()] > (0xFFF - I)) {
    V[0xF] = 1;
  } else {
    V[0xF] = 0;
  }
}
void Chip8::I_MEM(void) { I = V[get_x()] * 5; }
void Chip8::DEC_EQ(void) {
  uint8_t temp = V[get_x()];

  mem[I] = (temp / 100) % 10;
  mem[I + 1] = (temp / 10) % 10;
  mem[I + 2] = temp % 10;
}
void Chip8::STR_REG(void) {
  for (uint8_t z = 0; z <= get_x(); z++) {
    mem[I + z] = V[z];
  }
  I += (get_x() + 1);
}
void Chip8::LD_REG(void) {
  for (uint8_t z = 0; z <= get_x(); z++) {
    V[z] = mem[I + z];
  }
  I += (get_x() + 1);
}
void Chip8::fetch(void) {
  op = ((mem[program_counter] << 8) | mem[program_counter + 1]);
}
void Chip8::execute(void) { (this->*func_table[(op & 0xF000) >> 12])(); }
void Chip8::error_op(void) {
  std::cout << "Unkown opcode : " << std::hex << op << "\n";
}
uint8_t Chip8::getReg(uint8_t index) { return V[index]; }

void Chip8::choose_zero(void) {
  switch (op & 0x00FF) {
  case 0xE0: {
    CLEAR_SCR();
  } break;
  case 0xEE: {
    RET();
  } break;
  default: {
    error_op();
  }
  }
}
void Chip8::choose_eight(void) {
  switch (op & 0x000F) {
  case 0x0: {
    MOV_YX();
  } break;
  case 0x1: {
    OR_X();
  } break;
  case 0x2: {
    AND_X();
  } break;
  case 0x3: {
    XOR_X();
  } break;
  case 0x4: {
    ADDC_YX();
  } break;
  case 0x5: {
    SUBBOR_YX();
  } break;
  case 0x6: {
    SHIFTR();
  } break;
  case 0x7: {
    SUB_X();
  } break;
  case 0xE: {
    SHIFTL();
  } break;
  default: {
    error_op();
  }
  }
}
void Chip8::choose_e(void) {
  switch (op & 0x00FF) {
  case 0x9E: {
    SKIP_PRESS();
  } break;
  case 0xA1: {
    SKIP_NPRESS();
  } break;
  default: {
    error_op();
  }
  }
}

void Chip8::choose_f(void) {

  switch (op & 0x00FF) {
  case 0x07: {
    STR_DEL();
  } break;
  case 0x0A: {
    WAIT_KEY();
  } break;
  case 0x15: {
    SET_DEL();
  } break;
  case 0x18: {
    SET_SND();
  } break;
  case 0x1E: {
    ADD_I();
  } break;
  case 0x29: {
    I_MEM();
  } break;
  case 0x33: {
    DEC_EQ();
  } break;
  case 0x55: {
    STR_REG();
  } break;
  case 0x65: {
    LD_REG();
  } break;
  default: {
    error_op();
  }
  }
}

void Chip8::incPC(void) { program_counter += 2; }

bool Chip8::get_dflag(void) { return draw_flag; }
void Chip8::set_kflag(uint8_t index) {
  key_flag = true;
  key_index = index;
}
uint8_t Chip8::get_kflag(void) { return key_flag; }
uint8_t *Chip8::get_disp(void) { return display; }

void Chip8::set_keypad(uint8_t index, uint8_t val) { keypad[index] = val; }
