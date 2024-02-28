#ifndef _ERZC_CORE_PROGRAM_H
#define _ERZC_CORE_PROGRAM_H

#include <erzc/core/types.h>

/**
 * \file
 *
 * \brief \ref ERZC_Program "Program"'s routines
 */

/**
 * \brief Inits the \ref ERZC_Program "program".
 *
 * \details Sets all instructions to \ref ERZC_OP_UNDF "OP_UNDF" and all labels to \ref
 * ERZC_Label_END "Label_END".
 *
 * \note Implementation detail: \ref ERZC_Program_Reset "Program_Reset" macro expands directly into
 * this function call.
 *
 * \param[out] program program. **MUST NOT** be `NULL`
 */
void ERZC_Program_Init(ERZC_Program *program);

/**
 * \brief Resets the \ref ERZC_Program "program".
 *
 * \details Sets all instructions to \ref ERZC_OP_UNDF "OP_UNDF" and all labels to \ref
 * ERZC_Label_END "Label_END".
 *
 * \note Implementation detail: expands directly into \ref ERZC_Program_Init "Program_Init".
 *
 * \param[out] program program. **MUST NOT** be `NULL`
 */
#define ERZC_Program_Reset(program) ERZC_Program_Init(program)

#endif /* _ERZC_CORE_PROGRAM_H */
