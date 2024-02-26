#ifndef _ERZC_CORE_TYPES_H
#define _ERZC_CORE_TYPES_H

#if !defined(uint32_t) || !defined(UINT32_MAX)
#    include <stdint.h> /* available only since C99 */
#endif

#include <stddef.h> /* size_t */

/**
 * \file
 *
 * \brief Core types.
 *
 * \details
 *
 * \section terms Glossary:
 *
 * \subsubsection term_anonymous_labels Anonymous labels
 *
 * \note Do not confuse with \ref term_named_labels "named labels".
 *
 * \subsubsection term_input_instructions Input instructions
 *
 * Input instructions are instruction which compiler receives as input. Based on them the compiler
 * produces \ref term_output_instructions "output instructions".
 *
 * \note Input instruction can reference to quasi labels \ref ERZC_Label_END "END" and \ref
 * ERZC_Label_UNDEFINED "UNDEFINED" by their out pins.
 *
 * \sa \ref ERZC_InInstructions "InInstructions" - for typedef
 *
 * \subsubsection term_instruction Instruction
 *
 * \sa \ref ERZC_Instruction "Instruction" - for typedef
 *
 * \subsubsection term_named_labels Named labels
 *
 * \note Do not confuse with \ref term_anonymous_labels "anonymous labels".
 *
 * There are opcodes which moves PC to one of this labels:
 * + \ref ERZC_OP_GO0 "GO0"
 * + \ref ERZC_OP_GO1 "GO1"
 * + \ref ERZC_OP_GO2 "GO2"
 * + \ref ERZC_OP_GO3 "GO3"
 * + \ref ERZC_OP_GO4 "GO4"
 * + \ref ERZC_OP_GO5 "GO5"
 *
 * \sa \ref ERZC_NAMED_LABEL_NUMBER "NAMED_LABEL_NUMBER" - for the number of named labels in program
 *
 * \subsubsection term_output_instructions Output instructions
 *
 * Instructions that the compiler produces based on the \ref term_input_instructions
 * "input instructions". Output instruction are packed at \ref term_program "program".
 *
 * \note Output instructions can reference to quasi label \ref ERZC_Label_END "Label_END" by their
 * out pins.
 *
 * \subsubsection term_program Program
 *
 * Each program consists of lines. Each program line consists of \ref term_instruction
 * "instructions".
 *
 * \sa
 * + \ref ERZC_Program "Program" - for typedef
 * + \ref ERZC_WIDTH "WIDTH" - for the number of instruction per line
 * + \ref ERZC_HEIGHT "HEIGHT" - for the number of lines in program
 * + \ref ERZC_SIZE "SIZE" - for the number of instruction per program
 *
 * \subsubsection term_instruction_real Real instructions
 *
 * Instructions are called real if they interact with the real world in some way. In other words, in
 * general, each real input instruction must correspond to one output instruction.
 *
 * All real instructions have \ref ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err"
 * out pins. There are some real instructions that have only \ref ERZC_Instruction::ok "ok" out pin.
 * There are no real instructions that don't have both \ref ERZC_Instruction::ok "ok" and \ref
 * ERZC_Instruction::err "err" out pins.
 */

#ifndef ERZC_WIDTH
/**
 * \brief Number of instruction per line in program.
 *
 * \sa \ref ERZC_HEIGHT "HEIGHT", \ref ERZC_SIZE "SIZE"
 */
#    define ERZC_WIDTH 12u
#endif /* ERZC_WIDTH */

#ifndef ERZC_HEIGHT
/**
 * \brief Number of lines in one program.
 *
 * \sa \ref ERZC_WIDTH "WIDTH", \ref ERZC_SIZE "SIZE"
 */
#    define ERZC_HEIGHT 80u
#endif /* ERZC_HEIGHT */

/**
 * \brief Number of instructions in one program.
 *
 * \sa \ref ERZC_WIDTH "WIDTH", \ref ERZC_HEIGHT "HEIGHT"
 */
#define ERZC_SIZE (ERZC_WIDTH * ERZC_HEIGHT)

/**
 * \brief Maximum number of \ref term_named_labels "named labels" in program.
 */
#define ERZC_NAMED_LABEL_NUMBER 6u

/**
 * \brief Direction.
 */
typedef enum tagERZC_Direction {
    /**
     * \brief Up.
     */
    ERZC_Direction_UP = 3, /* 0b00'11 */
    /**
     * \brief Left.
     */
    ERZC_Direction_LEFT = 12, /* 0b11'00 */
    /**
     * \brief Down.
     */
    ERZC_Direction_DOWN = 1, /* 0b00'01 */
    /**
     * \brief Right.
     */
    ERZC_Direction_RIGHT = 4, /* 0b01'00 */
} ERZC_Direction;

/**
 * \brief Pin doesn't exist.
 *
 * \sa ERZC_OP "OP"
 */
#define ERZC_PIN_NONE 0
/**
 * \brief Pin exists.
 *
 * \sa ERZC_OP "OP"
 */
#define ERZC_PIN_SOME 10 /* NOTE: 0b10'10. MUST NOT COLLIDE WITH Direction! */

/**
 * \brief Anonymous Label.
 *
 * \details There are two kinds of anonymous label:
 * + real - points to the next instruction to execute
 * + quasi - does not point to instruction
 *
 * There are two quasi labels:
 * + \ref ERZC_Label_UNDEFINED "Label_UNDEFINED"
 * + \ref ERZC_Label_END "Label_END"
 *
 * Constants:
 * + \ref ERZC_Label_QUASI_MIN "Label_QUASI_MIN" minimum value of quasi label
 *
 * Interface:
 * + \ref ERZC_Label_IsQuasi "IsQuasi" - checks if the label is quasi
 * (following macros are for \ref term_output_instructions "output instructions" not-quasi labels
 * only):
 * + \ref ERZC_Label_GetX "Label_GetX" - returns `x` coordinate
 * + \ref ERZC_Label_GetY "Label_GetY" - returns `y` coordinate
 *
 * \sa \ref term_anonymous_labels "Anonymous labels" in \ref terms "Glossary"
 */
typedef uint32_t ERZC_Label;

/**
 * \brief Quasi \ref ERZC_Label "anonymous label" representing end of execution.
 *
 * \note Can be use by both \ref term_input_instructions "input" and \ref term_output_instructions
 * "output" instructions.
 *
 * \sa
 * + \ref ERZC_Label "ERZC_Label"
 * + \ref ERZC_Label_UNDEFINED "Label_UNDEFINED" - another quasi label
 */
#define ERZC_Label_END ((ERZC_Label)UINT32_MAX)
/**
 * \brief Quasi \ref ERZC_Label "anonymous label" representing that this label is not specified.
 *
 * \note Can be used only in \ref term_input_instructions "input instructions".
 *
 * \sa
 * + \ref ERZC_Label "ERZC_Label"
 * + \ref ERZC_Label_END "Label_END" - another quasi label
 */
#define ERZC_Label_UNDEFINED ((ERZC_Label)UINT32_MAX - 1)

/**
 * \brief Minimum value of any quasi \ref ERZC_Label "label".
 *
 * \sa \ref ERZC_Label_IsQuasi "Label_IsQuasi" - for checking if label is quasi
 */
#define ERZC_Label_QUASI_MIN ERZC_Label_UNDEFINED

/**
 * \brief Checks if the label is quasi.
 *
 * \param label \ref ERZC_Label "label"
 */
#define ERZC_Label_IsQuasi(label) ((ERZC_Label)(label) >= ERZC_Label_QUASI_MIN)

/**
 * \brief Returns `x` coordinate from label.
 *
 * \param label \ref ERZC_Label "label"
 *
 * \warning Can be used only at \ref term_output_instructions "output instructions" not-quasi
 * labels.
 */
#define ERZC_Label_GetX(label) (((ERZC_Label)(label) & (0xFFFFu << 0)) >> 0)
/**
 * \brief Returns `y` coordinate from label.
 *
 * \param label \ref ERZC_Label "label"
 *
 * \warning Can be used only at \ref term_output_instructions "output instructions" not-quasi
 * labels.
 */
#define ERZC_Label_GetY(label) (((ERZC_Label)(label) & (0xFFFF << 16)) >> 16)

#define __ERZC_OP_OK_RSHIFT 0
#define __ERZC_OP_OK_LABEL_RSHIFT 8
#define __ERZC_OP_ERR_RSHIFT 16
#define __ERZC_OP_NR_RSHIFT 24
#define __ERZC_OP_OK_LABEL(x)                                                                      \
    (((uint32_t)(x) << __ERZC_OP_OK_LABEL_RSHIFT) | (uint32_t)ERZC_PIN_SOME)

#define __ERZC_OP_BUILD(nr, ok, err)                                                               \
    (((uint32_t)(nr) << __ERZC_OP_NR_RSHIFT) | ((uint32_t)(ok) << __ERZC_OP_OK_RSHIFT) |           \
     (((uint32_t)(err) << __ERZC_OP_ERR_RSHIFT)))

#define __ERZC_OP_NR_REAL_MIN ((uint32_t)12)

/**
 * \brief Returns direction of ok out pin.
 *
 * \param op \ref ERZC_OP "op"
 *
 * \details Can be one of:
 * + \ref ERZC_PIN_NONE "PIN_NONE" - not exists
 * + \ref ERZC_Direction_UP "Direction_UP" - pointing upwards
 * + \ref ERZC_Direction_LEFT "Direction_LEFT" - pointing towards the left
 * + \ref ERZC_Direction_DOWN "Direction_DOWN" - pointing downwards
 * + \ref ERZC_Direction_RIGHT "Direction_RIGHT" - pointing to the right
 * + \ref ERZC_PIN_SOME "PIN_SOME" - pin exists and leads to:
 *   + (iff op is one of \ref ERZC_OP_GO0 "OP_GO0", \ref ERZC_OP_GO1 "OP_GO1", \ref ERZC_OP_GO2
 * "OP_GO2", \ref ERZC_OP_GO3 "OP_GO3", \ref ERZC_OP_GO4 "OP_GO4", \ref ERZC_OP_GO5 "OP_GO5") -
 * corresponding \ref term_named_labels "named label"
 *   + (iff op is \ref ERZC_OP_EMPTY "OP_EMPTY") - \ref ERZC_Label_END "end" of program
 */
#define ERZC_OP_GetOk(op) (((uint32_t)(op) & ((uint32_t)0xFFu << 0)) >> 0)
/**
 * \brief Returns index of \ref term_named_labels "named label".
 *
 * \param op \ref ERZC_OP "op"
 *
 * \warning Can be used only if \ref ERZC_OP_GetOk "OP_GetOk" equals to \ref ERZC_PIN_SOME
 * "PIN_SOME".
 */
#define ERZC_OP_GetOkLabel(op) (((uint32_t)(op) & ((uint32_t)0xFFu << 8)) >> 8)
/**
 * \brief Returns direction of err out pin.
 *
 * \param op \ref ERZC_OP "op"
 *
 * \details Can be one of:
 * + \ref ERZC_PIN_NONE "PIN_NONE" - not exists
 * + \ref ERZC_Direction_DOWN "Direction_DOWN" - pointing downwards
 */
#define ERZC_OP_GetErr(op) (((uint32_t)(op) & ((uint32_t)0xFFu << 16)) >> 16)
/**
 * \brief Returns opcode number.
 *
 * \param op \ref ERZC_OP "op"
 */
#define ERZC_OP_GetNr(op) (((uint32_t)(op) & ((uint32_t)0xFFu << 24)) >> 24)

/**
 * \brief Opcode.
 *
 * \details There is one quasi opcode - \ref ERZC_OP_UNDF "UNDF".
 *
 * Interface (works for quasi as well):
 * \ref ERZC_OP_GetOk "OP_GetOk" - ok pin direction
 * \ref ERZC_OP_GetOkLabel "OP_GetOkLabel" - ok pin \ref term_named_labels "named label" index
 * \ref ERZC_OP_GetErr "OP_GetErr" - err pin direction
 * \ref ERZC_OP_GetNr "OP_GetNr" - opcode number
 */
typedef enum __tagERZC_OP {
    /**
     * \brief Represents instruction that hasn't been set up yet.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has no out pins.
     */
    ERZC_OP_UNDF = __ERZC_OP_BUILD(0, ERZC_PIN_NONE, ERZC_PIN_NONE),
    /**
     * \brief Noop.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only on out pin
     * - \ref ERZC_Instruction::ok "ok" which always referencing to the \ref ERZC_Label_END "end" of
     * the program.
     */
    ERZC_OP_EMPTY = __ERZC_OP_BUILD(1, ERZC_PIN_SOME, ERZC_PIN_NONE),
    /**
     * \brief Move PC up.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_PCW = __ERZC_OP_BUILD(2, ERZC_Direction_UP, ERZC_PIN_NONE),
    /**
     * \brief Move PC left.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_PCA = __ERZC_OP_BUILD(3, ERZC_Direction_LEFT, ERZC_PIN_NONE),
    /**
     * \brief Move PC down.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_PCS = __ERZC_OP_BUILD(4, ERZC_Direction_DOWN, ERZC_PIN_NONE),
    /**
     * \brief Move PC right.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_PCD = __ERZC_OP_BUILD(5, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `0`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO0 = __ERZC_OP_BUILD(6, __ERZC_OP_OK_LABEL(0), ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `1`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO1 = __ERZC_OP_BUILD(7, __ERZC_OP_OK_LABEL(1), ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `2`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO2 = __ERZC_OP_BUILD(8, __ERZC_OP_OK_LABEL(2), ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `3`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO3 = __ERZC_OP_BUILD(9, __ERZC_OP_OK_LABEL(3), ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `4`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO4 = __ERZC_OP_BUILD(10, __ERZC_OP_OK_LABEL(4), ERZC_PIN_NONE),
    /**
     * \brief Goto \ref term_named_labels "named labels" with index `5`.
     *
     * \details This instruction isn't \ref term_instruction_real "real" and it has only one out pin
     * \ref ERZC_Instruction::ok "ok".
     */
    ERZC_OP_GO5 = __ERZC_OP_BUILD(11, __ERZC_OP_OK_LABEL(5), ERZC_PIN_NONE),

    /**
     * \brief Tries to move diggeroid forward.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_MOVE =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Tries to move diggeroid forward.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_DIG =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 1u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Tries to move diggeroid forward.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_MOVDG =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 2u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Turns the diggeroid 45 degrees clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_RC045 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 3u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 90 degrees clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_RC090 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 4u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 135 degrees clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_RC135 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 5u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 180 degrees.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_RC180 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 6u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 45 degrees counter-clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_CC045 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 7u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 90 degrees counter-clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_CC090 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 8u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Turns the diggeroid 135 degrees counter-clockwise.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has one out pin \ref
     * ERZC_Instruction::ok "ok".
     */
    ERZC_OP_CC135 =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 9u, ERZC_Direction_RIGHT, ERZC_PIN_NONE),
    /**
     * \brief Scans the cell for `walkable` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_SWLK =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 10u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `notWalkable` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_NWLK =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 11u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `diggable` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_SDIG =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 12u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `notDiggable` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_NDIG =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 13u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `crystal` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_SCRS =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 14u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `notCrystal` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_NCRS =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 15u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `handmade` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_SHND =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 10u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
    /**
     * \brief Scans the cell for `notHandmade` property.
     *
     * \details This instruction is \ref term_instruction_real "real" and it has two out pins - \ref
     * ERZC_Instruction::ok "ok" and \ref ERZC_Instruction::err "err".
     */
    ERZC_OP_NHND =
        __ERZC_OP_BUILD(__ERZC_OP_NR_REAL_MIN + 11u, ERZC_Direction_RIGHT, ERZC_Direction_DOWN),
} ERZC_OP;

/**
 * \brief Instruction.
 *
 * \sa \ref term_instruction "Instruction" in \ref terms "Glossary"
 */
typedef struct __tagERZC_Instruction {
    /**
     * \brief Opcode.
     */
    ERZC_OP op;
    /**
     * \brief Ok out pin.
     *
     * \details References the next instruction to be executed upon successful execution of this
     * instruction.
     *
     * \note There are two instructions that don't have this pin - \ref ERZC_OP_UNDF "OP_UNDEF"
     * and \ref ERZC_OP_EMPTY "OP_EMPTY". Both of them are not \ref term_instruction_real "real".
     *
     * \note In \ref term_input_instructions "input instructions" this field can be set quasi
     * labels \ref ERZC_Label_END "Label_END" and \ref ERZC_Label_UNDEFINED "Label_UNDEFINED".
     * \note In \ref term_output_instructions "output instructions" this field can be set to
     * quasi label \ref ERZC_Label_END "Label_END".
     */
    ERZC_Label ok;
    /**
     * \brief Err out pin.
     *
     * \details References the next instruction to be executed upon failed execution of this
     * instruction.
     *
     * \warning Not all instructions have this pin. All instructions that have this pin are \ref
     * term_instruction_real "real" (but the opposite is not true).
     *
     * \note In \ref term_input_instructions "input instructions" this field can be set quasi
     * labels \ref ERZC_Label_END "Label_END" and \ref ERZC_Label_UNDEFINED "Label_UNDEFINED".
     * \note In \ref term_output_instructions "output instructions" this field can be set to
     * quasi label \ref ERZC_Label_END "Label_END".
     */
    ERZC_Label err;
} ERZC_Instruction;

/**
 * \brief Program.
 *
 * \sa \ref term_program "Program" in \ref terms "Glossary"
 */
typedef struct __tagERZC_Program {
    /**
     * \brief One-dimensional array of instructions.
     */
    ERZC_Instruction data[ERZC_SIZE];
    /**
     * \brief Array of \ref term_named_labels "named labels".
     */
    ERZC_Label labels[ERZC_NAMED_LABEL_NUMBER];
} ERZC_Program;

/**
 * \brief Input instructions.
 *
 * \details Flat array of instructions pointing to each other by labels as indexes.
 *
 * \section req Requirements:
 *
 * Opcode of any reachable instruction mustn't be \ref ERZC_OP_UNDF "UNDF".
 *
 * Label of any reachable instruction must be on of:
 * + valid index in the array
 * + \ref ERZC_Label_END "END"
 * + \ref ERZC_Label_UNDEFINED "UNDEFINED" - if one don't care about what instruction will be
 * executed next
 *
 * They only allowed to use \ref term_anonymous_labels "anonymous labels" so they can't
 * contain any opcodes of:
 * + \ref ERZC_OP_GO0 "GO0"
 * + \ref ERZC_OP_GO1 "GO1"
 * + \ref ERZC_OP_GO2 "GO2"
 * + \ref ERZC_OP_GO3 "GO3"
 * + \ref ERZC_OP_GO4 "GO4"
 * + \ref ERZC_OP_GO5 "GO5"
 *
 * \sa \ref term_input_instructions "Input instructions" in \ref terms "Glossary"
 */
typedef struct __tagERZC_InInstructions {
    /**
     * \brief Length.
     *
     * \warning Must be less or equal than \ref ERZC_Label_UNDEFINED "UNDEFINED".
     */
    size_t len;
    /**
     * \brief Array of instructions.
     */
    ERZC_Instruction *data;
} ERZC_InInstructions;

#endif /* _ERZC_CORE_TYPES_H */
