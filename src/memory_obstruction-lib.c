/* Module used for creating a memory obstruction using mmap
   Copyright (C) 2024 Free Software Foundation, Inc.
   Copyright The GNU Toolchain Authors.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If
   not, see <https://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

static void *obstruction_addr = NULL;
static long page_size;

/* ELF constructor to set up the obstruction */
static void obstruction_setup (void) __attribute__ ((constructor));

/* ELF destructor to teardown the obstruction */
static void obstruction_teardown (void) __attribute__ ((destructor));

static void
obstruction_setup (void)
{
  /* Get the runtime page size */
  page_size = sysconf (_SC_PAGESIZE);

  /* Get current program break */
  void *current_brk = sbrk (0);

  /* Round up to the next page boundary */
  void *next_page_boundary
      = (void *) (((unsigned long) current_brk + page_size - 1)
		  & ~(page_size - 1));

  /* Place a mapping using mmap at the next page boundary */
  obstruction_addr = mmap (next_page_boundary, page_size, PROT_READ,
			   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (obstruction_addr == MAP_FAILED)
    {
      fprintf (stderr, "obstruction setup mmap: %s\n", strerror (errno));
      obstruction_addr = NULL;
    }
}

/* Function to teardown the obstruction mapping */
static void
obstruction_teardown (void)
{
  /* Free the obstruction mapping */
  if (obstruction_addr && munmap (obstruction_addr, page_size) == -1)
    {
      fprintf (stderr, "tear down munmap: %s\n", strerror (errno));
    }
}
