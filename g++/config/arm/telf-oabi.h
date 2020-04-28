/* CYGNUS LOCAL (entire file) clm/arm-elf */
/* Definitions of target machine for GNU compiler,
   for Thumb with ELF obj format.
   Copyright (C) 1995, 1996, 1997, 1998, 1999 Free Software Foundation, Inc.
   
This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#define OBJECT_FORMAT_ELF

#define CPP_PREDEFINES "-Darm_oabi -Dthumb -Dthumbelf -D__thumb -Acpu(arm) -Amachine(arm)"

#define ASM_SPEC "-moabi -marm7tdmi %{mthumb-interwork:-mthumb-interwork} %{mbig-endian:-EB}"

#include "arm/thumb.h"

/* Run-time Target Specification.  */
#undef TARGET_VERSION
#define TARGET_VERSION fputs (" (Thumb/elf)", stderr)

#define MULTILIB_DEFAULTS { "mlittle-endian" }

/* Setting this to 32 produces more efficient code, but the value set in previous
   versions of this toolchain was 8, which produces more compact structures. The
   command line option -mstructure_size_boundary=<n> can be used to change this
   value.  */
#undef STRUCTURE_SIZE_BOUNDARY
#define STRUCTURE_SIZE_BOUNDARY arm_structure_size_boundary

extern int arm_structure_size_boundary;

/* Debug */
#define DWARF_DEBUGGING_INFO
#define DWARF2_DEBUGGING_INFO
#define PREFERRED_DEBUGGING_TYPE DWARF2_DEBUG


/* Note - it is important that these definitions match those in semi.h for the ARM port.  */
#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."


/* A C statement to output assembler commands which will identify the
   object file as having been compiled with GNU CC (or another GNU
   compiler).  */
#define ASM_IDENTIFY_GCC(STREAM)				\
     fprintf (STREAM, "%sgcc2_compiled.:\n", LOCAL_LABEL_PREFIX )

#undef ASM_FILE_START
#define ASM_FILE_START(STREAM) \
do {								\
  extern char *version_string;					\
  fprintf ((STREAM), "%s Generated by gcc %s for Thumb/elf\n", \
	   ASM_COMMENT_START, version_string);	                \
  fprintf ((STREAM), ASM_APP_OFF);                              \
} while (0)

/* A C statement to output something to the assembler file to switch to section
   NAME for object DECL which is either a FUNCTION_DECL, a VAR_DECL or
   NULL_TREE.  Some target formats do not support arbitrary sections.  Do not
   define this macro in such cases.  */
#define ASM_OUTPUT_SECTION_NAME(STREAM, DECL, NAME, RELOC) \
do {								\
  if ((DECL) && TREE_CODE (DECL) == FUNCTION_DECL)		\
    fprintf (STREAM, "\t.section %s,\"ax\",@progbits\n", (NAME));		\
  else if ((DECL) && DECL_READONLY_SECTION (DECL, RELOC))	\
    fprintf (STREAM, "\t.section %s,\"a\"\n", (NAME));		\
  else								\
    fprintf (STREAM, "\t.section %s,\"aw\"\n", (NAME));		\
} while (0)

/* Support the ctors/dtors and other sections.  */

#undef INIT_SECTION_ASM_OP

/* Define this macro if jump tables (for `tablejump' insns) should be
   output in the text section, along with the assembler instructions.
   Otherwise, the readonly data section is used.  */
#define JUMP_TABLES_IN_TEXT_SECTION 1

#undef READONLY_DATA_SECTION
#define READONLY_DATA_SECTION	rdata_section
#undef RDATA_SECTION_ASM_OP
#define RDATA_SECTION_ASM_OP	"\t.section .rodata"

#undef  CTORS_SECTION_ASM_OP
#define CTORS_SECTION_ASM_OP	"\t.section .ctors,\"aw\""
#undef  DTORS_SECTION_ASM_OP
#define DTORS_SECTION_ASM_OP	"\t.section .dtors,\"aw\""

#define USER_LABEL_PREFIX ""

/* Don't know how to order these.  UNALIGNED_WORD_ASM_OP is in
   dwarf2.out. */ 
#define UNALIGNED_WORD_ASM_OP ".4byte"

#define ASM_OUTPUT_DWARF2_ADDR_CONST(FILE,ADDR)				\
     if (((ADDR)[0] == '.') && ((ADDR)[1] == 'L')) 			\
       fprintf ((FILE), "\t%s\t%s", UNALIGNED_WORD_ASM_OP, (ADDR));	\
     else                                                     		\
       fprintf ((FILE), "\t%s\t%s",					\
             UNALIGNED_WORD_ASM_OP, (ADDR))

#define ASM_OUTPUT_DWARF_ADDR_CONST(FILE,RTX)                   \
do {								\
  fprintf ((FILE), "\t%s\t", UNALIGNED_WORD_ASM_OP);		\
  output_addr_const ((FILE), (RTX));				\
  fputc ('\n', (FILE));						\
} while (0)

/* This is how to equate one symbol to another symbol.  The syntax used is
   `SYM1=SYM2'.  Note that this is different from the way equates are done
   with most svr4 assemblers, where the syntax is `.set SYM1,SYM2'.  */

#define ASM_OUTPUT_DEF(FILE,LABEL1,LABEL2)				\
 do {	fprintf ((FILE), "\t");						\
	assemble_name (FILE, LABEL1);					\
	fprintf (FILE, " = ");						\
	assemble_name (FILE, LABEL2);					\
	fprintf (FILE, "\n");						\
  } while (0)

/* A list of other sections which the compiler might be "in" at any
   given time.  */
#undef EXTRA_SECTIONS
#define EXTRA_SECTIONS SUBTARGET_EXTRA_SECTIONS in_rdata, in_ctors, in_dtors

#define SUBTARGET_EXTRA_SECTIONS

/* A list of extra section function definitions.  */

#undef EXTRA_SECTION_FUNCTIONS
#define EXTRA_SECTION_FUNCTIONS \
  RDATA_SECTION_FUNCTION	\
  CTORS_SECTION_FUNCTION	\
  DTORS_SECTION_FUNCTION	\
  SUBTARGET_EXTRA_SECTION_FUNCTIONS

#define SUBTARGET_EXTRA_SECTION_FUNCTIONS

#define RDATA_SECTION_FUNCTION \
void									\
rdata_section ()							\
{									\
  if (in_section != in_rdata)						\
    {									\
      fprintf (asm_out_file, "%s\n", RDATA_SECTION_ASM_OP);		\
      in_section = in_rdata;						\
    }									\
}

#define CTOR_LIST_BEGIN                                 \
asm (CTORS_SECTION_ASM_OP);                             \
func_ptr __CTOR_LIST__[1] = { (func_ptr) (-1) }

#define CTOR_LIST_END                                   \
asm (CTORS_SECTION_ASM_OP);                             \
func_ptr __CTOR_END__[1] = { (func_ptr) 0 };

#define DTOR_LIST_BEGIN                                 \
asm (DTORS_SECTION_ASM_OP);                             \
func_ptr __DTOR_LIST__[1] = { (func_ptr) (-1) }

#define DTOR_LIST_END                                   \
asm (DTORS_SECTION_ASM_OP);                             \
func_ptr __DTOR_END__[1] = { (func_ptr) 0 };

#define CTORS_SECTION_FUNCTION \
void									\
ctors_section ()							\
{									\
  if (in_section != in_ctors)						\
    {									\
      fprintf (asm_out_file, "%s\n", CTORS_SECTION_ASM_OP);		\
      in_section = in_ctors;						\
    }									\
}

#define DTORS_SECTION_FUNCTION \
void									\
dtors_section ()							\
{									\
  if (in_section != in_dtors)						\
    {									\
      fprintf (asm_out_file, "%s\n", DTORS_SECTION_ASM_OP);		\
      in_section = in_dtors;						\
    }									\
}

/* Support the ctors/dtors sections for g++.  */

#define INT_ASM_OP ".word"

#define INVOKE__main

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crtbegin%O%s crt0%O%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend%O%s"

/* A C statement (sans semicolon) to output an element in the table of
   global constructors.  */
#undef ASM_OUTPUT_CONSTRUCTOR
#define ASM_OUTPUT_CONSTRUCTOR(STREAM,NAME) \
do {						\
  ctors_section ();				\
  fprintf (STREAM, "\t%s\t ", INT_ASM_OP);	\
  assemble_name (STREAM, NAME);			\
  fprintf (STREAM, "\n");			\
} while (0)

/* A C statement (sans semicolon) to output an element in the table of
   global destructors.  */
#undef ASM_OUTPUT_DESTRUCTOR
#define ASM_OUTPUT_DESTRUCTOR(STREAM,NAME) \
do {						\
  dtors_section ();                   		\
  fprintf (STREAM, "\t%s\t ", INT_ASM_OP);	\
  assemble_name (STREAM, NAME);              	\
  fprintf (STREAM, "\n");			\
} while (0)

/* The ARM development system has atexit and doesn't have _exit,
   so define this for now.  */
#define HAVE_ATEXIT

/* The ARM development system defines __main.  */
#define NAME__MAIN "__gccmain"
#define SYMBOL__MAIN __gccmain
