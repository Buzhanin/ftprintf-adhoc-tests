/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppernati <ppernati@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:17:12 by ppernati          #+#    #+#             */
/*   Updated: 2026/05/17 23:24:09 by ppernati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glib.h>
#include <locale.h>
#include "ft_printf.h"
#include <stdio.h>

#ifdef ORIGINAL
	#define ft_printf printf
#endif

typedef struct {
  int fd;
} FdFixture;

void	simple(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf(""), ==, 0);
		g_assert_cmpuint(ft_printf("Test"), ==, 4);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("Test");
}

void	percent(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%%"), ==, 1);
		g_assert_cmpuint(ft_printf("%%Test%%"), ==, 6);
		g_assert_cmpuint(ft_printf("%%Test"), ==, 5);
		g_assert_cmpuint(ft_printf("Test%%"), ==, 5);
		g_assert_cmpuint(ft_printf("Test%%Test"), ==, 9);
		g_assert_cmpuint(ft_printf("%%%%%%"), ==, 3);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("%%Test%%TestTest%Test%Test%%%");
}

void	integer_i(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%i", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%i", 5), ==, 1);
		g_assert_cmpuint(ft_printf("%i***", 100), ==, 6);
		g_assert_cmpuint(ft_printf("**%i", 2147483647), ==, 12);
		g_assert_cmpuint(ft_printf("##%i##", (int)-2147483648), ==, 15);
		g_assert_cmpuint(ft_printf("%i%i%i", 1, -2, 3), ==, 4);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("05100*****2147483647##-2147483648##1-23");
}

void	integer_d(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%d", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%d", 5), ==, 1);
		g_assert_cmpuint(ft_printf("%d***", 100), ==, 6);
		g_assert_cmpuint(ft_printf("**%d", 2147483647), ==, 12);
		g_assert_cmpuint(ft_printf("##%d##", (int)-2147483648), ==, 15);
		g_assert_cmpuint(ft_printf("%d%d%d", 1, -2, 3), ==, 4);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("05100*****2147483647##-2147483648##1-23");
}
void	unsigned_integer(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%u", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%u", 5), ==, 1);
		g_assert_cmpuint(ft_printf("%u***", 100), ==, 6);
		g_assert_cmpuint(ft_printf("**%u", (unsigned int)4294967295), ==, 12);
		g_assert_cmpuint(ft_printf("##%u##", (int)-2147483648), ==, 14);
		g_assert_cmpuint(ft_printf("%u%u%u", 1, -2, 3), ==, 12);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("05100*****4294967295##2147483648##142949672943");
}


void	character(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%c", '1'), ==, 1);
		g_assert_cmpuint(ft_printf("%c", 'A'), ==, 1);
		g_assert_cmpuint(ft_printf("%c***", '='), ==, 4);
		g_assert_cmpuint(ft_printf("**%c", '\200'), ==, 3);
		g_assert_cmpuint(ft_printf("##%c##", ' '), ==, 5);
		g_assert_cmpuint(ft_printf("%c%c%c", '1', (char)-2, '3'), ==, 3);
		g_assert_cmpuint(ft_printf("%c%c%c", '\0', '\0', '\0'), ==, 3);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("1A=*****\200## ##1\3763");
}

void	string(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%s", (char *)NULL), ==, 6);
		g_assert_cmpuint(ft_printf("%s", ""), ==, 0);
		g_assert_cmpuint(ft_printf("%s##", "HA"), ==, 4);
		g_assert_cmpuint(ft_printf("##%s", "HA"), ==, 4);
		g_assert_cmpuint(ft_printf("##%s##", "HO"), ==, 6);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("(null)HA####HA##HO##");
}

void	pointer(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%p", NULL), ==, 3);
		g_assert_cmpuint(ft_printf("%p", (void*)100), ==, 4);
		g_assert_cmpuint(ft_printf("%p", (void*)-100), ==, 18);
		g_assert_cmpuint(ft_printf("%p", (void*)1000000000000000000), ==, 17);
		g_assert_cmpuint(ft_printf("%p", (void*)9223372036854775807), ==, 18);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("0x00x640xffffffffffffff9c0xde0b6b3a76400000x7fffffffffffffff");
}
void	hex(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%x", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%x", -10), ==, 8);
		g_assert_cmpuint(ft_printf("%x", (unsigned int)4294967295), ==, 8);
		g_assert_cmpuint(ft_printf("%x", (unsigned int)-2147483648), ==, 8);
		g_assert_cmpuint(ft_printf("%x", 2147483647), ==, 8);
		g_assert_cmpuint(ft_printf("%x", 11259375), ==, 6);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("0fffffff6ffffffff800000007fffffffabcdef");
}

void	upperhex(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%X", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%X", -10), ==, 8);
		g_assert_cmpuint(ft_printf("%X", (unsigned int)4294967295), ==, 8);
		g_assert_cmpuint(ft_printf("%X", (unsigned int)-2147483648), ==, 8);
		g_assert_cmpuint(ft_printf("%X", 2147483647), ==, 8);
		g_assert_cmpuint(ft_printf("%X", 11259375), ==, 6);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("0FFFFFFF6FFFFFFFF800000007FFFFFFFABCDEF");
}

void	mixed(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%d, %i, %s%c||%x-%x=%p Sure it's not fail", 3, 4, "test", '!', 256, 512, (void *)100500), ==, 47);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("3, 4, test!||100-200=0x18894 Sure it's not fail");
}

void	hash(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%#x", 1024), ==, 5);
		g_assert_cmpuint(ft_printf("%#X", 1024), ==, 5);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("0x4000X400");
}

void	space(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("% d", 1024), ==, 5);
		g_assert_cmpuint(ft_printf("% d", -1024), ==, 5);
		g_assert_cmpuint(ft_printf("% i", 1024), ==, 5);
		g_assert_cmpuint(ft_printf("% i", -1024), ==, 5);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout(" 1024-1024 1024-1024");
}

void	plus(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%+d", 1024), ==, 5);
		g_assert_cmpuint(ft_printf("%+d", -1024), ==, 5);
		g_assert_cmpuint(ft_printf("%+i", 1024), ==, 5);
		g_assert_cmpuint(ft_printf("%+i", -1024), ==, 5);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("+1024-1024+1024-1024");
}

void	width(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("[%10s]", "hello"), ==, 12);
		g_assert_cmpuint(ft_printf("[%-10s]", "hello"), ==, 12);
		g_assert_cmpuint(ft_printf("[%10i]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%-+10d]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%- 10d]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%-1d]", 100), ==, 5);
		g_assert_cmpuint(ft_printf("[%1d]", 100), ==, 5);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("[     hello][hello     ][       100][+100      ][ 100      ][100][100]");
}

void	precision(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("[%10.2s]", "hello"), ==, 12);
		g_assert_cmpuint(ft_printf("[%-+10.5i]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%10.0s]", "hello"), ==, 12);
		g_assert_cmpuint(ft_printf("[%-+10.0i]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%.0i]", 0), ==, 2);
		g_assert_cmpuint(ft_printf("[%-+10.i]", 100), ==, 12);
		g_assert_cmpuint(ft_printf("[%.i]", 0), ==, 2);
		g_assert_cmpuint(ft_printf("[%.7x]", 100), ==, 9);
		g_assert_cmpuint(ft_printf("[%.7x]", 0), ==, 9);
		g_assert_cmpuint(ft_printf("[%#.7x]", 100), ==, 11);
		g_assert_cmpuint(ft_printf("[%#.7x]", 0), ==, 9);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("[        he][+00100    ][          ][+100      ][][+100      ][][0000064][0000000][0x0000064][0000000]");
}

void	zero(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("[%010s]", "hi"), ==, 12);
		g_assert_cmpuint(ft_printf("[%010i]", 500), ==, 12);
		g_assert_cmpuint(ft_printf("[%+010i]", 500), ==, 12);
		g_assert_cmpuint(ft_printf("[% 010i]", 500), ==, 12);
		g_assert_cmpuint(ft_printf("[% 010.2i]", 500), ==, 12);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("[0000000500][+000000500][ 000000500][       500]");
}

int	main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/ft_printf/simple", simple);
	g_test_add_func("/ft_printf/character", character);
	g_test_add_func("/ft_printf/string", string);
	g_test_add_func("/ft_printf/pointer", pointer);
	g_test_add_func("/ft_printf/integer_i", integer_i);
	g_test_add_func("/ft_printf/integer_d", integer_d);
	g_test_add_func("/ft_printf/unsigned_integer", unsigned_integer);
	g_test_add_func("/ft_printf/hex", hex);
	g_test_add_func("/ft_printf/upperhex", upperhex);
	g_test_add_func("/ft_printf/percent", percent);
	g_test_add_func("/ft_printf/mixed", mixed);
	g_test_add_func("/ft_printf_bonus/hash", hash);
	g_test_add_func("/ft_printf_bonus/space", space);
	g_test_add_func("/ft_printf_bonus/plus", plus);
	g_test_add_func("/ft_printf_bonus/width", width);
	g_test_add_func("/ft_printf_bonus/precision", precision);
	g_test_add_func("/ft_printf_bonus/zero", zero);
	return (g_test_run());
}
