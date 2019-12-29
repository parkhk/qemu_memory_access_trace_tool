diff -ruN d4-7/config.log dinero/config.log
--- d4-7/config.log	2014-06-02 16:10:32.106317266 -0400
+++ dinero/config.log	2014-06-02 16:10:32.404313175 -0400
@@ -16,55 +16,55 @@
 configure:834: gcc -E  conftest.c >/dev/null 2>conftest.out
 configure:901: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
 configure: In function 'main':
-configure:896:1: warning: implicit declaration of function 'exit' [-Wimplicit-function-declaration]
-configure:896:67: warning: incompatible implicit declaration of built-in function 'exit' [enabled by default]
+configure:896:1: warning: implicit declaration of function 'exit'
+configure:896:67: warning: incompatible implicit declaration of built-in function 'exit'
 configure:926: checking for working const
 configure:980: gcc -c -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes  conftest.c 1>&5
 configure: In function 'main':
-configure:950:5: warning: cast discards '__attribute__((const))' qualifier from pointer target type [-Wcast-qual]
-configure:954:15: warning: unused variable 's' [-Wunused-variable]
-configure:959:7: warning: declaration of 'x' shadows a previous local [-Wshadow]
-configure:936:39: warning: shadowed declaration is here [-Wshadow]
-configure:965:8: warning: declaration of 'p' shadows a previous local [-Wshadow]
-configure:939:8: warning: shadowed declaration is here [-Wshadow]
-configure:974:13: warning: unused variable 'foo' [-Wunused-variable]
-configure:942:27: warning: unused variable 'zero' [-Wunused-variable]
-configure:936:39: warning: unused variable 'x' [-Wunused-variable]
-configure:956:8: warning: 't' is used uninitialized in this function [-Wuninitialized]
-configure:971:21: warning: 'b' is used uninitialized in this function [-Wuninitialized]
+configure:950:1: warning: cast discards qualifiers from pointer target type
+configure:954:15: warning: unused variable 's'
+configure:959:7: warning: declaration of 'x' shadows a previous local
+configure:936:39: warning: shadowed declaration is here
+configure:965:8: warning: declaration of 'p' shadows a previous local
+configure:939:8: warning: shadowed declaration is here
+configure:974:13: warning: unused variable 'foo'
+configure:942:27: warning: unused variable 'zero'
+configure:936:39: warning: unused variable 'x'
+configure:956:8: warning: 't' is used uninitialized in this function
+configure:971:21: warning: 'b' is used uninitialized in this function
 configure:1001: checking for size_t
 configure:1034: checking size of short
 configure:1053: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
-configure:1044:1: warning: return type defaults to 'int' [-Wreturn-type]
+configure:1044:1: warning: return type defaults to 'int'
 configure: In function 'main':
-configure:1047:3: warning: implicit declaration of function 'exit' [-Wimplicit-function-declaration]
-configure:1047:11: warning: incompatible implicit declaration of built-in function 'exit' [enabled by default]
-configure:1048:3: warning: format '%d' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Wformat]
+configure:1047:3: warning: implicit declaration of function 'exit'
+configure:1047:11: warning: incompatible implicit declaration of built-in function 'exit'
+configure:1048:3: warning: format '%d' expects type 'int', but argument 3 has type 'long unsigned int'
 configure:1073: checking size of int
 configure:1092: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
-configure:1083:1: warning: return type defaults to 'int' [-Wreturn-type]
+configure:1083:1: warning: return type defaults to 'int'
 configure: In function 'main':
-configure:1086:3: warning: implicit declaration of function 'exit' [-Wimplicit-function-declaration]
-configure:1086:11: warning: incompatible implicit declaration of built-in function 'exit' [enabled by default]
-configure:1087:3: warning: format '%d' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Wformat]
+configure:1086:3: warning: implicit declaration of function 'exit'
+configure:1086:11: warning: incompatible implicit declaration of built-in function 'exit'
+configure:1087:3: warning: format '%d' expects type 'int', but argument 3 has type 'long unsigned int'
 configure:1112: checking size of long
 configure:1131: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
-configure:1122:1: warning: return type defaults to 'int' [-Wreturn-type]
+configure:1122:1: warning: return type defaults to 'int'
 configure: In function 'main':
-configure:1125:3: warning: implicit declaration of function 'exit' [-Wimplicit-function-declaration]
-configure:1125:11: warning: incompatible implicit declaration of built-in function 'exit' [enabled by default]
-configure:1126:3: warning: format '%d' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Wformat]
+configure:1125:3: warning: implicit declaration of function 'exit'
+configure:1125:11: warning: incompatible implicit declaration of built-in function 'exit'
+configure:1126:3: warning: format '%d' expects type 'int', but argument 3 has type 'long unsigned int'
 configure:1151: checking size of void*
 configure:1170: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
-configure:1161:1: warning: return type defaults to 'int' [-Wreturn-type]
+configure:1161:1: warning: return type defaults to 'int'
 configure: In function 'main':
-configure:1164:3: warning: implicit declaration of function 'exit' [-Wimplicit-function-declaration]
-configure:1164:11: warning: incompatible implicit declaration of built-in function 'exit' [enabled by default]
-configure:1165:3: warning: format '%d' expects argument of type 'int', but argument 3 has type 'long unsigned int' [-Wformat]
+configure:1164:3: warning: implicit declaration of function 'exit'
+configure:1164:11: warning: incompatible implicit declaration of built-in function 'exit'
+configure:1165:3: warning: format '%d' expects type 'int', but argument 3 has type 'long unsigned int'
 configure:1195: checking for random
 configure:1223: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
 configure:1195: checking for modf
 configure:1223: gcc -o conftest -O3 -g -Wall -Wcast-qual -Wshadow -Wpointer-arith -Wmissing-prototypes   conftest.c  1>&5
-configure:1207:6: warning: conflicting types for built-in function 'modf' [enabled by default]
+configure:1207:6: warning: conflicting types for built-in function 'modf'
 configure:1346: checking if random is defined in stdlib.h
 configure:1373: checking whether make sets ${MAKE}
diff -ruN d4-7/config.status dinero/config.status
--- d4-7/config.status	2014-06-02 16:10:32.291314726 -0400
+++ dinero/config.status	2014-06-02 16:10:32.551311157 -0400
@@ -2,7 +2,7 @@
 # Generated automatically by configure.
 # Run this file to recreate the current configuration.
 # This directory was configured as follows,
-# on host parkhk.system:
+# on host baekdoo.cs.pitt.edu:
 #
 # ./configure 
 #
Binary files d4-7/libd4.a and dinero/libd4.a differ
diff -ruN d4-7/results.park dinero/results.park
--- d4-7/results.park	1969-12-31 19:00:00.000000000 -0500
+++ dinero/results.park	2014-06-02 16:10:32.404313175 -0400
@@ -0,0 +1,118 @@
+---Dinero IV cache simulator, version 7
+---Written by Jan Edler and Mark D. Hill
+---Copyright (C) 1997 NEC Research Institute, Inc. and Mark D. Hill.
+---All rights reserved.
+---Copyright (C) 1985, 1989 Mark D. Hill.  All rights reserved.
+---See -copyright option for details
+
+---Summary of options (-help option gives usage information).
+
+-l2-usize 262144
+-l3-usize 8388608
+-l1-isize 32768
+-l1-dsize 32768
+-l2-ubsize 64
+-l3-ubsize 64
+-l1-ibsize 64
+-l1-dbsize 64
+-l2-usbsize 64
+-l3-usbsize 64
+-l1-isbsize 64
+-l1-dsbsize 64
+-l2-uassoc 8
+-l3-uassoc 16
+-l1-iassoc 4
+-l1-dassoc 4
+-l2-urepl l
+-l3-urepl l
+-l1-irepl l
+-l1-drepl l
+-l2-ufetch d
+-l3-ufetch d
+-l1-ifetch d
+-l1-dfetch d
+-l2-uwalloc a
+-l3-uwalloc a
+-l1-dwalloc a
+-l2-uwback a
+-l3-uwback a
+-l1-dwback a
+-skipcount 0
+-flushcount 0
+-maxcount 0
+-stat-interval 0
+-informat d
+-on-trigger 0x0
+-off-trigger 0x0
+
+---Simulation begins.
+---Simulation complete.
+l1-icache
+ Metrics		      Total	      Instrn	       Data	       Read	      Write	       Misc
+ -----------------	      ------	      ------	      ------	      ------	      ------	      ------
+ Demand Fetches		       87218	       87218	           0	           0	           0	           0
+  Fraction of total	      1.0000	      1.0000	      0.0000	      0.0000	      0.0000	      0.0000
+
+ Demand Misses		       15723	       15723	           0	           0	           0	           0
+  Demand miss rate	      0.1803	      0.1803	      0.0000	      0.0000	      0.0000	      0.0000
+
+ Multi-block refs                 0
+ Bytes From Memory	     1006272
+ ( / Demand Fetches)	     11.5374
+ Bytes To Memory	           0
+ ( / Demand Writes)	      0.0000
+ Total Bytes r/w Mem	     1006272
+ ( / Demand Fetches)	     11.5374
+
+l1-dcache
+ Metrics		      Total	      Instrn	       Data	       Read	      Write	       Misc
+ -----------------	      ------	      ------	      ------	      ------	      ------	      ------
+ Demand Fetches		      388543	           0	      388543	      224706	      163837	           0
+  Fraction of total	      1.0000	      0.0000	      1.0000	      0.5783	      0.4217	      0.0000
+
+ Demand Misses		       72199	           0	       72199	       48238	       23961	           0
+  Demand miss rate	      0.1858	      0.0000	      0.1858	      0.2147	      0.1462	      0.0000
+
+ Multi-block refs                 0
+ Bytes From Memory	     4620736
+ ( / Demand Fetches)	     11.8925
+ Bytes To Memory	     1567744
+ ( / Demand Writes)	      9.5689
+ Total Bytes r/w Mem	     6188480
+ ( / Demand Fetches)	     15.9274
+
+l2-ucache
+ Metrics		      Total	      Instrn	       Data	       Read	      Write	       Misc
+ -----------------	      ------	      ------	      ------	      ------	      ------	      ------
+ Demand Fetches		      112418	       15723	       96695	       72199	       24496	           0
+  Fraction of total	      1.0000	      0.1399	      0.8601	      0.6422	      0.2179	      0.0000
+
+ Demand Misses		       61658	        7210	       54448	       54428	          20	           0
+  Demand miss rate	      0.5485	      0.4586	      0.5631	      0.7539	      0.0008	      0.0000
+
+ Multi-block refs                 0
+ Bytes From Memory	     3944832
+ ( / Demand Fetches)	     35.0908
+ Bytes To Memory	     1489088
+ ( / Demand Writes)	     60.7890
+ Total Bytes r/w Mem	     5433920
+ ( / Demand Fetches)	     48.3367
+
+l3-ucache
+ Metrics		      Total	      Instrn	       Data	       Read	      Write	       Misc
+ -----------------	      ------	      ------	      ------	      ------	      ------	      ------
+ Demand Fetches		       84905	        7210	       77695	       54428	       23267	           0
+  Fraction of total	      1.0000	      0.0849	      0.9151	      0.6410	      0.2740	      0.0000
+
+ Demand Misses		       48306	        3391	       44915	       44911	           4	           0
+  Demand miss rate	      0.5689	      0.4703	      0.5781	      0.8251	      0.0002	      0.0000
+
+ Multi-block refs                 0
+ Bytes From Memory	     3091328
+ ( / Demand Fetches)	     36.4093
+ Bytes To Memory	     1458240
+ ( / Demand Writes)	     62.6742
+ Total Bytes r/w Mem	     4549568
+ ( / Demand Fetches)	     53.5842
+
+---Execution complete.
