#include <erzc/core/program.h>

#include <erzc/common/assert.h>

#include <mir/common/macros.h>

#include <stddef.h> /* NULL */

void ERZC_Program_Init(ERZC_Program *program) {
    size_t i;
    ERZC_Label *label;
    ERZC_Instruction *instruction;

    ERZC_ASSERT_MSG(program != NULL, "param `program' MUST NOT be NULL");

    MIR_FOREACH (program->data, ERZC_SIZE, &i, &instruction) {
        instruction->op = ERZC_OP_UNDF;
    }

    MIR_FOREACH (program->labels, ERZC_NAMED_LABEL_NUMBER, &i, &label) {
        *label = ERZC_Label_END;
    }
}
