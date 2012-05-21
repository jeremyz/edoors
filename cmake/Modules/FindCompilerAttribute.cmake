INCLUDE(CheckCSourceCompiles)
SET(HAVE___ATTRIBUTE__)
CHECK_C_SOURCE_COMPILES(
   "void  foo (int bar __attribute__((unused)) ) { }
   static void baz (void) __attribute__((unused));
   static void baz (void) { }
   int main(){}
   " HAVE___ATTRIBUTE__
   )
