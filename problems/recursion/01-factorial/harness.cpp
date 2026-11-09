TEST("n = 0", "factorial(0)") { CHECK("factorial(0)", factorial(0), 1); }
TEST("n = 1", "factorial(1)") { CHECK("factorial(1)", factorial(1), 1); }
TEST("n = 2", "factorial(2)") { CHECK("factorial(2)", factorial(2), 2); }
TEST("n = 5", "factorial(5)") { CHECK("factorial(5)", factorial(5), 120); }
TEST("n = 10", "factorial(10)") { CHECK("factorial(10)", factorial(10), 3628800); }
TEST("n = 12", "factorial(12)") { CHECK("factorial(12)", factorial(12), 479001600); }
