Linear equations solver
=============================

See https://en.wikipedia.org/wiki/Gaussian_elimination for Gauss-Jordan's
algorithm and its uses for solving systems of linear equations.

Compiling
---------

Use the ``make`` command to compile the program. The default compiler is GCC.

.. code-block:: shell

	$ make
	$ ./lineqsolve

Input format
---------------

In the file ``matrix.txt`` are entered the integers coefficients of the matrixes
separated by a single space (and none at the end of the lines). On each line are
the coefficients and the constant (result), creating in the end one more column
than there are lines.

The following system of equations

.. math::

	 x + 2y &= 3\\
	4x + 5y &= 6

would be represented in the text file as::

	1 2 3
	4 5 6

License
---------

Copyright © 2021  e10e3

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see https://www.gnu.org/licenses/.
