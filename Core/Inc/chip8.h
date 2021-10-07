#pragma once

#define RAM_SIZE 4096
#define ROM_SIZE 3584
#define DISP_SIZE 2048
#define DISP_WIDTH 64
#define DISP_HEIGHT 32
#define GREG_SIZE 16
#define FONTSET_SIZE 80

#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

class Chip8 {
public:
  Chip8();
  ~Chip8();

  void init(void);               // Initialize vars
  void emulate(void);            // Read and execute instruction
  uint8_t getReg(uint8_t index); // Get value of general purpose reg
  void JUMP(void);

  void choose_zero(void);
  void choose_eight(void);
  void choose_e(void);
  void choose_f(void);

  void CALL(void);
  void SKIP_FEQ(void);
  void SKIP_NEQ(void);
  void SKIP_YXEQ(void);
  void MOV_X(void);
  void ADD_X(void);

  void SKIP_YXNEQ(void);
  void STR_ADDR(void);
  void JUMP_V0(void);
  void RAND(void);
  void DRAW(void);

  bool get_dflag(void);
  bool load(char *filename);
  uint8_t *get_disp(void);
  void set_kflag(uint8_t index);
  void set_keypad(uint8_t index, uint8_t val);
  uint8_t get_kflag(void);

private:
  uint16_t op;              // 16 bit opcode
  uint16_t I;               // Index register
  uint16_t program_counter; // Program Counter
  uint16_t sp;              // Stack Pointer
  uint8_t delay_timer;      // Used to coordinate events
  uint8_t sound_timer;      // buzzes when reaches 0
  uint8_t key_index;
  bool jump_flag;
  bool draw_flag;
  bool key_flag;

  uint8_t
      mem[RAM_SIZE]; // Size of RAM is 4k, byte addressable. 0x000-0xFFF FIXME
  /*RAM map
   *0x000-0x1FF   :   Chip8 interpreter
   *0x050-0x0A0   :   Built in 4x5 pixel font (letters, num)
   *0x200-0xE8F   :   Program ROM
   *0xE90-0xFFF   :   Variables and displya refresh
   */
  uint8_t V[GREG_SIZE]; // 16 8-bit General purpose registers,reg 16 being a
                        // carry flag reg
  uint8_t display[DISP_SIZE]; // Pixels on screen
  uint8_t keypad[16];         // FIXME
  uint16_t stack[16];         // Saves current pc before subroutine

  uint8_t get_x();
  uint8_t get_y();
  uint8_t get_nn();

  using func_p = void (Chip8::*)(void);
  std::array<func_p, 16> func_table = {
      &Chip8::choose_zero, &Chip8::JUMP,     &Chip8::CALL,
      &Chip8::SKIP_FEQ,    &Chip8::SKIP_NEQ, &Chip8::SKIP_YXEQ,
      &Chip8::MOV_X,       &Chip8::ADD_X,    &Chip8::choose_eight,
      &Chip8::SKIP_YXNEQ,  &Chip8::STR_ADDR, &Chip8::JUMP_V0,
      &Chip8::RAND,        &Chip8::DRAW,     &Chip8::choose_e,
      &Chip8::choose_f};

  void incPC(void);
  void fetch(void);
  void execute(void);
  void error_op(void);

  void CLEAR_SCR(void);
  void RET(void);

  void MOV_YX(void);
  void OR_X(void);
  void AND_X(void);
  void XOR_X(void);
  void ADDC_YX(void);
  void SUBBOR_YX(void);
  void SHIFTR(void);
  void SUB_X(void);
  void SHIFTL(void);

  void SKIP_PRESS(void);
  void SKIP_NPRESS(void);

  void STR_DEL(void);
  void WAIT_KEY(void);
  void SET_DEL(void);
  void SET_SND(void);
  void ADD_I(void);
  void I_MEM(void);
  void DEC_EQ(void);
  void STR_REG(void);
  void LD_REG(void);
};