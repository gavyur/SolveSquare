/*
    SolveSquare v1
    Copyright (C) 2015 Yury Gavrilov <yuriy@igavrilov.ru>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <float.h>
#include <math.h>

/*! \mainpage SolveSquare documentation

    SolveSquare is a program for solving square equations

    See the documentation for \link ./main.c \endlink file
 */

/*!
    \brief Number of allowed incorrect input in `input()`
 */
const int ERR_INPUT_TRIES = 3;
/*!
    \brief Constant for equations that have infinite number of roots
 */
const int INFINITE_ROOTS = -1;

int input(const char name[], double* value);
void clear_stdin();
int solve_square(double a, double b, double c, double* x1, double* x2);
int solve_linear(double b, double c, double* x);

/*!
    \brief Main function

    Get source data and print result.
 */
int main()
{
    printf("#--- SolveSquare v1 (%s %s) by GavYur\n\n", __DATE__, __TIME__);

    printf("#--- Let's find roots for equation Ax^2 + Bx + C = 0:\n");
    double a = 0, b = 0, c = 0;
    if (!input("A", &a))
        return 0;
    if (!input("B", &b))
        return 0;
    if (!input("C", &c))
        return 0;
    double x1 = 0, x2 = 0;
    int roots_num = solve_square(a, b, c, &x1, &x2);
    if (roots_num == INFINITE_ROOTS)
        printf("#--- This equation has infinite number of roots\n");
    else if (roots_num == 0)
        printf("#--- This equation has no roots\n");
    else if (roots_num == 1)
        printf("#--- This equation has one root:\nx = %lg\n", x1);
    else if (roots_num == 2)
        printf("#--- This equation has two roots:\nx1 = %lg\nx2 = %lg\n", x1, x2);
    else
        printf("#--- Something strange happened, please remember A, B and C numbers and contact author");

    return 0;
}

/*!
    \brief Read floating point number variable from stdin.

    If user entered incorrect input, asks it again #ERR_INPUT_TRIES times.

    \param[in] name name of variable
    \param[out] value pointer to variable location

    \return 1 if success else 0
 */
int input(const char name[], double* value)
{
    int tries = 0;
    int result = 0;
    while ((tries < ERR_INPUT_TRIES) && (result == 0))
    {
        printf("#--- Enter a real-number value for %s> ", name);
        result = scanf("%lg", value);
        if (result == 0)
        {
            ++tries;
            clear_stdin();
            printf("#--- Incorrect input!");
            if (tries < ERR_INPUT_TRIES)
                printf(" Let's try again!\n");
            else
                printf(" That was last try :(\n");
        }
    }
    return result;
}

/*!
    \brief Move stdin to next line.

    When `scanf()` gets incorrect input, it stops reading stdin,
    but we need to read numbers next time from new line.

    This function moves position of reading stdin to begin of new line.
 */
void clear_stdin()
{
    char trash[256];// = {};
    scanf("%s", trash);
}

/*!
    \brief Solve square equation

    Find roots for square equation \f$ax^2+bx+c=0\f$

    \param[in] a a coefficient (of \f$x^2\f$)
    \param[in] b b coefficient (of \f$x\f$)
    \param[in] c c coefficient
    \param[out] x1 pointer to first root location
    \param[out] x2 pointer to second root location

    \return number of roots or #INFINITE_ROOTS
 */
int solve_square(double a, double b, double c, double* x1, double* x2)
{
    if (fabs(a) < DBL_EPSILON)
        return solve_linear(b, c, x1);

    double d = b * b - 4 * a * c;
    if ((d < 0) && (fabs(d) > DBL_EPSILON)))
    {
        return 0;
    } else if (fabs(d) < DBL_EPSILON)
    {
        *x1 = -b / (2 * a);
        return 1;
    } else
    {
        d = sqrt(d);
        *x1 = (-b - d) / (2 * a);
        *x2 = (-b + d) / (2 * a);
        return 2;
    }
}

/*!
    \brief Solve linear equation

    Find roots for linear equation \f$bx+c=0\f$

    \param[in] b b coefficient (of \f$x\f$)
    \param[in] c c coefficient
    \param[out] x pointer to root location

    \return number of roots or #INFINITE_ROOTS
 */
int solve_linear(double b, double c, double* x)
{
    if (fabs(b) < DBL_EPSILON)
    {
        if (fabs(c) < DBL_EPSILON)
            return INFINITE_ROOTS;
        else
            return 0;
    }

    *x = -c / b;
    return 1;
}
