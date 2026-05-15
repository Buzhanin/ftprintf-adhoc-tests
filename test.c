/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppernati <ppernati@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:17:12 by ppernati          #+#    #+#             */
/*   Updated: 2026/05/15 18:35:36 by ppernati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glib.h>
#include <locale.h>
#include "ft_printf.h"
#include <stdio.h>

#if 1
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

void	integer(void)
{
	if (g_test_subprocess())
	{
		g_assert_cmpuint(ft_printf("%i", 0), ==, 1);
		g_assert_cmpuint(ft_printf("%i", 5), ==, 1);
		g_assert_cmpuint(ft_printf("%i***", 100), ==, 6);
		g_assert_cmpuint(ft_printf("**%i", 2147483647), ==, 12);
		g_assert_cmpuint(ft_printf("##%i##", (int)-2147483648), ==, 15);
		g_assert_cmpuint(ft_printf("%i%d%i", 1, -2, 3), ==, 4);
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
		g_assert_cmpuint(ft_printf("%i", 0), ==, 1);
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
		g_assert_cmpuint(ft_printf("%c", '\0'), ==, 1);
		g_assert_cmpuint(ft_printf("%c", 'A'), ==, 1);
		g_assert_cmpuint(ft_printf("%c***", '='), ==, 4);
		g_assert_cmpuint(ft_printf("**%c", '\200'), ==, 3);
		g_assert_cmpuint(ft_printf("##%c##", ' '), ==, 5);
		g_assert_cmpuint(ft_printf("%c%c%c", '1', (char)-2, '3'), ==, 3);
		return;
	}

	g_test_trap_subprocess(NULL, 3000000, 0);
	g_test_trap_assert_passed();
	g_test_trap_assert_stdout("1A=*****\200## ##1\3763");
}

int	main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/ft_printf/simple", simple);
	g_test_add_func("/ft_printf/percent", percent);
	g_test_add_func("/ft_printf/integer", integer);
	g_test_add_func("/ft_printf/unsigned_integer", unsigned_integer);
	g_test_add_func("/ft_printf/character", character);
	return (g_test_run());
}
