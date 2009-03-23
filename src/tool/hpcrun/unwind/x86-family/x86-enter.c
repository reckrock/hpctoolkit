/******************************************************************************
 * include files
 *****************************************************************************/

#include "x86-interval-highwatermark.h"
#include "pmsg.h"



/******************************************************************************
 * interface operations 
 *****************************************************************************/

unwind_interval *
process_enter(char *ins, xed_decoded_inst_t *xptr, const xed_inst_t *xi, 
	      unwind_interval *current, highwatermark_t *highwatermark)
{
  unsigned int i;
  unwind_interval *next;

  long offset = 8;

  for(i = 0; i < xed_inst_noperands(xi) ; i++) {
    const xed_operand_t *op =  xed_inst_operand(xi,i);
    switch (xed_operand_name(op)) {
    case XED_OPERAND_IMM0SIGNED:
      offset += xed_decoded_inst_get_signed_immediate(xptr);
      break;
    default:
      break;
    }
  }
  PMSG(INTV,"new interval from ENTER");
  next = new_ui(ins + xed_decoded_inst_get_length(xptr),
		RA_STD_FRAME,
		current->sp_ra_pos + offset, 8, BP_SAVED,
		current->sp_bp_pos + offset - 8, 0, current);
  highwatermark->uwi = next;
  highwatermark->state = 
    HW_NEW_STATE(highwatermark->state, HW_BP_SAVED | 
		 HW_SP_DECREMENTED | HW_BP_OVERWRITTEN);
  return next;
}

