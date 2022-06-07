# Polynomial algebraic expressions
Project related to the course "Advanced Programming" @ Units. The goal is to build a tool able to handle basic operations with polynomial expressions.

## Problem description
A *polynomial algebraic expression* is either:
- a *variable*
- a constant value in $\mathbb{Z}$
- the sum, the subtracion, or the product of two polynomial algebraic expressions.

For instance, $(x - 4 * y + 3) * x - 2$, $z * z$, and $0$ are all polynomial algebraic expressions having 2, 1, and 0 variables, respectively.
The polynomial algebraic expressions $e_1$ and $e_2$ are *equivalent*  whenever the former can be rewritten as the latter by:
- interpreting the sums, subtractions, and products between constants as the standard arithmetic over $\mathbb{Z}$, e.g., $-3 + 1 * 5$ and 2 are equivalent;
- assuming the commutative law, e.g., $x * (y + 2)$ and $x + 3$ are equivalent to $(2 + y) * x$ and $3 + x$.
- accepting the distributive law,  e.g., $(x + 3) * y$ is equivalent to $x * y + 3 * y$, respectively.
If  $e$ is a polynomial algebraic expression and $x$ one of its variables, then $e$ can be rewritten as an equivalent polynomial algebraic expression:
$$a_0x^0 + a_1x^1 + ... + a_{n_x}x^{n_x}$$ where $x^i$ denotes the i-th natural power of $x$, $n_x$ is the maximum degree of $x$ in $e$, and the $a_i$'s are the (possible non-constants) $x$-coefficients of $e$ of degree $i$. For instance, $(x-4 * y+3) * x-2$ is equivalent to
$$-2 * x^0 + (3 - 4 * y) * x^1 + 1 * x^2$$
Thus, -2, (3 - 4 * y), and 1 are the expression $x$-coefficients of degree 0, 1, and 2, respectively.
