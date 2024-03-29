# OS Simulator

This is a special project of the operating system course I took.
The idea is to create an OS that simulates activity of a real system.

It reads 2 data files: 
* 1. OS parameters: Each record would be a new
simulation of your OS executing.
* 2. Data Input: Each record would
be a program with its runtime characteristics: CPU, i/o needs.

Then it uses a clock cycle and simulate and output what is happenging
in the system level.

Here is an example of what this program do.

### Input Data
Operating System Parameters:
```
   Mem   Blk   Num   Max   Pro.  Init  Disk Tape CD    Print
   Mode  Size  Blks  Proc. Alg.  Qtm.  unts unts unts  every-N-unts

 1) F    5000  20    10    FIFO  10     3    3    3      50
 2) F    5000  10    10    FIFO  10     3    3    3      50
 3) F    5000  20    10    IPRI  10     3    3    3      50
 4) F    5000  10    10    IPRI  10     3    3    3      50
```

Input Data for Problem:
```
   Program  Memory  Init. Run-Time Characteristics
    Name     Needs   Pri.

 1) GOODPGM   40      3    10, 20-1| 8, 20-1| 8, 20-1|10, 20-1| 8, 20-1| 8
 2) ARTSCLS  120      2    10, 30-1|10, 30-1| 5, 30-1|10, 30-1|10, 30-1| 5
 3) WAYTOGO   20      4     5,100-1| 5,100-1| 5,100-1| 5,100-1| 5,100-1| 5
 4) BARNONE   20      5    10, 50-1|10, 50-1|16, 50-1|10, 50-1|16, 50-1|14
 5) HONEYDO   50      2    20,  7-1|20,  4-1|25,  3-1|25,  7-1|20, 10-1| 5
 6) OVERDUE   20      4     5,100-1| 5,100-1| 5,100-1| 5,100-1| 5,100-1| 5
 7) BLASTED   20      5    15, 50-1|15, 50-1|15, 50-1|15, 50-1|15, 50-1|15
 8) XOXOXOX   10      3     4,  7-1| 4,  7-1| 4,  7-1| 4,  7-1| 4,  7-1| 4
 9) NONEMAN   40      1     5,100-1| 5,100-1| 5,100-1| 5,100-1| 5,100-1| 5
10) HOTSTUF   10      1    10, 20-1|10, 20-1|10
```

### Output Data
Output data frst list the input program requirement and output the simluation result:

```
Input Data List # 1 Contains:
  Name     : GOODPGM
  Init_Prio: 3
  Memsize  : 40
  i=0, j=0 : 10
  i=0, j=1 : 20
  i=0, j=2 : 1
  i=1, j=0 : 8
  i=1, j=1 : 20
  i=1, j=2 : 1
  i=2, j=0 : 8
  i=2, j=1 : 20
  i=2, j=2 : 1
  i=3, j=0 : 10
  i=3, j=1 : 20
  i=3, j=2 : 1
  i=4, j=0 : 8
  i=4, j=1 : 20
  i=4, j=2 : 1
  i=5, j=0 : 8
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 2 Contains:
  Name     : ARTSCLS
  Init_Prio: 2
  Memsize  : 120
  i=0, j=0 : 10
  i=0, j=1 : 30
  i=0, j=2 : 1
  i=1, j=0 : 10
  i=1, j=1 : 30
  i=1, j=2 : 1
  i=2, j=0 : 5
  i=2, j=1 : 30
  i=2, j=2 : 1
  i=3, j=0 : 10
  i=3, j=1 : 30
  i=3, j=2 : 1
  i=4, j=0 : 10
  i=4, j=1 : 30
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 3 Contains:
  Name     : WAYTOGO
  Init_Prio: 4
  Memsize  : 20
  i=0, j=0 : 5
  i=0, j=1 : 100
  i=0, j=2 : 1
  i=1, j=0 : 5
  i=1, j=1 : 100
  i=1, j=2 : 1
  i=2, j=0 : 5
  i=2, j=1 : 100
  i=2, j=2 : 1
  i=3, j=0 : 5
  i=3, j=1 : 100
  i=3, j=2 : 1
  i=4, j=0 : 5
  i=4, j=1 : 100
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 4 Contains:
  Name     : BARNONE
  Init_Prio: 5
  Memsize  : 20
  i=0, j=0 : 10
  i=0, j=1 : 50
  i=0, j=2 : 1
  i=1, j=0 : 10
  i=1, j=1 : 50
  i=1, j=2 : 1
  i=2, j=0 : 16
  i=2, j=1 : 50
  i=2, j=2 : 1
  i=3, j=0 : 10
  i=3, j=1 : 50
  i=3, j=2 : 1
  i=4, j=0 : 16
  i=4, j=1 : 50
  i=4, j=2 : 1
  i=5, j=0 : 14
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 5 Contains:
  Name     : HONEYDO
  Init_Prio: 2
  Memsize  : 50
  i=0, j=0 : 20
  i=0, j=1 : 7
  i=0, j=2 : 1
  i=1, j=0 : 20
  i=1, j=1 : 4
  i=1, j=2 : 1
  i=2, j=0 : 25
  i=2, j=1 : 3
  i=2, j=2 : 1
  i=3, j=0 : 25
  i=3, j=1 : 7
  i=3, j=2 : 1
  i=4, j=0 : 20
  i=4, j=1 : 10
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 6 Contains:
  Name     : OVERDUE
  Init_Prio: 4
  Memsize  : 20
  i=0, j=0 : 5
  i=0, j=1 : 100
  i=0, j=2 : 1
  i=1, j=0 : 5
  i=1, j=1 : 100
  i=1, j=2 : 1
  i=2, j=0 : 5
  i=2, j=1 : 100
  i=2, j=2 : 1
  i=3, j=0 : 5
  i=3, j=1 : 100
  i=3, j=2 : 1
  i=4, j=0 : 5
  i=4, j=1 : 100
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 7 Contains:
  Name     : BLASTED
  Init_Prio: 5
  Memsize  : 20
  i=0, j=0 : 15
  i=0, j=1 : 50
  i=0, j=2 : 1
  i=1, j=0 : 15
  i=1, j=1 : 50
  i=1, j=2 : 1
  i=2, j=0 : 15
  i=2, j=1 : 50
  i=2, j=2 : 1
  i=3, j=0 : 15
  i=3, j=1 : 50
  i=3, j=2 : 1
  i=4, j=0 : 15
  i=4, j=1 : 50
  i=4, j=2 : 1
  i=5, j=0 : 15
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 8 Contains:
  Name     : XOXOXOX
  Init_Prio: 3
  Memsize  : 10
  i=0, j=0 : 4
  i=0, j=1 : 7
  i=0, j=2 : 1
  i=1, j=0 : 4
  i=1, j=1 : 7
  i=1, j=2 : 1
  i=2, j=0 : 4
  i=2, j=1 : 7
  i=2, j=2 : 1
  i=3, j=0 : 4
  i=3, j=1 : 7
  i=3, j=2 : 1
  i=4, j=0 : 4
  i=4, j=1 : 7
  i=4, j=2 : 1
  i=5, j=0 : 4
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 9 Contains:
  Name     : NONEMAN
  Init_Prio: 1
  Memsize  : 40
  i=0, j=0 : 5
  i=0, j=1 : 100
  i=0, j=2 : 1
  i=1, j=0 : 5
  i=1, j=1 : 100
  i=1, j=2 : 1
  i=2, j=0 : 5
  i=2, j=1 : 100
  i=2, j=2 : 1
  i=3, j=0 : 5
  i=3, j=1 : 100
  i=3, j=2 : 1
  i=4, j=0 : 5
  i=4, j=1 : 100
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Input Data List # 10 Contains:
  Name     : HOTSTUF
  Init_Prio: 1
  Memsize  : 10
  i=0, j=0 : 10
  i=0, j=1 : 20
  i=0, j=2 : 1
  i=1, j=0 : 10
  i=1, j=1 : 20
  i=1, j=2 : 1
  i=2, j=0 : 10
  i=2, j=1 : 100
  i=2, j=2 : 1
  i=3, j=0 : 5
  i=3, j=1 : 100
  i=3, j=2 : 1
  i=4, j=0 : 5
  i=4, j=1 : 100
  i=4, j=2 : 1
  i=5, j=0 : 5
  i=5, j=1 : 0
  i=5, j=2 : 0

Starting O/S Simulation: 1. Version 5

O/S Parameters:

   Memory Model Used:      F
   Fixed Mem Blk Size:     5000
   Fixed Mem Blks Aval:    20
   Variable Mem Max Size:  0
   Variable Mem Tot Size:  0
   Max. Tasks Allowed:     10
   Process Mgmt Algthm:    FIFO   
   Initial Quantum Size:   10
   Number Disk Units:      3
   Number Tape Units:      3
   Number CD   Units:      3
   Print Every N Units:    50


Allocated: GOODPGM at MC time: 3  (PID#: 1)
   Memory Block(s): 1 2 3 4 5 6 7 8

Flushed: ARTSCLS from input queue - not enough memory!

Allocated: BARNONE at MC time: 3  (PID#: 2)
   Memory Block(s): 9 10 11 12

Allocated: WAYTOGO at MC time: 3  (PID#: 3)
   Memory Block(s): 13 14 15 16

Allocated: OVERDUE at MC time: 3  (PID#: 4)
   Memory Block(s): 17 18 19 20

Started: GOODPGM at MC time: 4

Started: BARNONE at MC time: 19

Started: WAYTOGO at MC time: 34

Started: OVERDUE at MC time: 49

=================================== 50 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Ready       1
2    BARNONE   9 10 11 12                    Blocked           1-2    I:83
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:148
4    OVERDUE   17 18 19 20                   Executing                T:60

     FreeBlks:
=================================== 50 ===================================

=================================== 100 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Blocked           1-2    I:106
2    BARNONE   9 10 11 12                    Blocked           PENDG
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:148
4    OVERDUE   17 18 19 20                   Blocked           1-3    I:158

     FreeBlks:
     IOS                                 Execute Next
=================================== 100 ===================================

=================================== 150 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Blocked           PENDG
2    BARNONE   9 10 11 12                    Blocked           1-2    I:159
3    WAYTOGO   13 14 15 16                   Ready       1
4    OVERDUE   17 18 19 20                   Blocked           1-3    I:158

     FreeBlks:
     IOS                                 Execute Next
=================================== 150 ===================================

=================================== 200 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Executing                T:210
2    BARNONE   9 10 11 12                    Ready       1
3    WAYTOGO   13 14 15 16                   Blocked           1-3    I:266
4    OVERDUE   17 18 19 20                   Blocked           1-1    I:286

     FreeBlks:
=================================== 200 ===================================

=================================== 250 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Blocked           PENDG
2    BARNONE   9 10 11 12                    Blocked           1-2    I:286
3    WAYTOGO   13 14 15 16                   Blocked           1-3    I:266
4    OVERDUE   17 18 19 20                   Blocked           1-1    I:286

     FreeBlks:
     DISPATCH                            Execute Next
=================================== 250 ===================================

=================================== 300 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Ready       2
2    BARNONE   9 10 11 12                    Held
3    WAYTOGO   13 14 15 16                   Blocked           1-2    I:389
4    OVERDUE   17 18 19 20                   Ready       1

     FreeBlks:
     DISPATCH                            Execute Next
=================================== 300 ===================================

Completed: GOODPGM at MC time: 333

De-Allocated: GOODPGM at MC time 336
  Total Service Units: 100
  Total CPU Units    : 52
  MC Start Time      : 4
  MC End Time        : 333
  Total Elapsed Units: 329
  Memory Blks Used   :  1 2 3 4 5 6 7 8

Allocated: BLASTED at MC time: 340  (PID#: 5)
   Memory Block(s): 1 2 3 4

Allocated: XOXOXOX at MC time: 340  (PID#: 6)
   Memory Block(s): 5 6

Allocated: HOTSTUF at MC time: 340  (PID#: 7)
   Memory Block(s): 7 8

Started: BLASTED at MC time: 341

=================================== 350 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
2    BARNONE   9 10 11 12                    Blocked           1-1    I:364
3    WAYTOGO   13 14 15 16                   Blocked           1-2    I:389
4    OVERDUE   17 18 19 20                   Blocked           1-3    I:424
5    BLASTED   1 2 3 4                       Executing                T:352
6    XOXOXOX   5 6                           Ready       1
7    HOTSTUF   7 8                           Ready       2

     FreeBlks:
=================================== 350 ===================================

Started: XOXOXOX at MC time: 353

Started: HOTSTUF at MC time: 362

=================================== 400 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
2    BARNONE   9 10 11 12                    Ready       1
3    WAYTOGO   13 14 15 16                   Ready       3
4    OVERDUE   17 18 19 20                   Blocked           1-3    I:424
5    BLASTED   1 2 3 4                       Blocked           PENDG
6    XOXOXOX   5 6                           Ready       2
7    HOTSTUF   7 8                           Blocked           1-1    I:406

     FreeBlks:
     IOS                                 Execute Next
=================================== 400 ===================================

=================================== 450 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
2    BARNONE   9 10 11 12                    Ready       1
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:547
4    OVERDUE   17 18 19 20                   Ready       2
5    BLASTED   1 2 3 4                       Blocked           1-2    I:451
6    XOXOXOX   5 6                           Ready       3
7    HOTSTUF   7 8                           Executing                T:459

     FreeBlks:
=================================== 450 ===================================

=================================== 500 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
2    BARNONE   9 10 11 12                    Blocked           1-3    I:528
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:547
4    OVERDUE   17 18 19 20                   Blocked           1-2    I:593
5    BLASTED   1 2 3 4                       Ready       1
6    XOXOXOX   5 6                           Blocked           PENDG
7    HOTSTUF   7 8                           Ready       2

     FreeBlks:
     IOS                                 Execute Next
=================================== 500 ===================================

=================================== 550 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
2    BARNONE   9 10 11 12                    Held
3    WAYTOGO   13 14 15 16                   Blocked           DONE
4    OVERDUE   17 18 19 20                   Blocked           1-2    I:593
5    BLASTED   1 2 3 4                       Blocked           PENDG
6    XOXOXOX   5 6                           Ready       1
7    HOTSTUF   7 8                           Blocked           1-3    I:649

     FreeBlks:
     DISPATCH                            Execute Next
=================================== 550 ===================================

Completed: BARNONE at MC time: 590

De-Allocated: BARNONE at MC time 593
  Total Service Units: 250
  Total CPU Units    : 76
  MC Start Time      : 19
  MC End Time        : 590
  Total Elapsed Units: 571
  Memory Blks Used   :  9 10 11 12

=================================== 600 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    WAYTOGO   13 14 15 16                   Blocked           PENDG
4    OVERDUE   17 18 19 20                   Ready       1
5    BLASTED   1 2 3 4                       Blocked           1-1    I:604
6    XOXOXOX   5 6                           Blocked           PENDG
7    HOTSTUF   7 8                           Blocked           1-3    I:649

     FreeBlks: 9 10 11 12
     IOS                                 Execute Next
=================================== 600 ===================================

=================================== 650 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:707
4    OVERDUE   17 18 19 20                   Blocked           1-2    I:722
5    BLASTED   1 2 3 4                       Held
6    XOXOXOX   5 6                           Blocked           PENDG
7    HOTSTUF   7 8                           Ready       1

     FreeBlks: 9 10 11 12
     IOS                                 Execute Next
=================================== 650 ===================================

Completed: XOXOXOX at MC time: 678

De-Allocated: XOXOXOX at MC time 681
  Total Service Units: 35
  Total CPU Units    : 24
  MC Start Time      : 353
  MC End Time        : 678
  Total Elapsed Units: 325
  Memory Blks Used   :  5 6

=================================== 700 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    WAYTOGO   13 14 15 16                   Blocked           1-1    I:707
4    OVERDUE   17 18 19 20                   Blocked           1-2    I:722
5    BLASTED   1 2 3 4                       Blocked           1-3    I:713
7    HOTSTUF   7 8                           Blocked           PENDG

     FreeBlks: 5 6 9 10 11 12
     IDLE                                Execute Next
=================================== 700 ===================================

Completed: WAYTOGO at MC time: 721

De-Allocated: WAYTOGO at MC time 724
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 34
  MC End Time        : 721
  Total Elapsed Units: 687
  Memory Blks Used   :  13 14 15 16

Allocated: HONEYDO at MC time: 728  (PID#: 8)
   Memory Block(s): 5 6 9 10 11 12 13 14 15 16

Started: HONEYDO at MC time: 746

=================================== 750 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
4    OVERDUE   17 18 19 20                   Ready       1
5    BLASTED   1 2 3 4                       Ready       2
7    HOTSTUF   7 8                           Blocked           1-1    I:810
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Executing                T:757

     FreeBlks:
=================================== 750 ===================================

Completed: OVERDUE at MC time: 763

De-Allocated: OVERDUE at MC time 766
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 49
  MC End Time        : 763
  Total Elapsed Units: 714
  Memory Blks Used   :  17 18 19 20

=================================== 800 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
5    BLASTED   1 2 3 4                       Blocked           1-2    I:830
7    HOTSTUF   7 8                           Blocked           1-1    I:810
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Blocked           1-3    I:802

     FreeBlks: 17 18 19 20
     IDLE                                Execute Next
=================================== 800 ===================================

=================================== 850 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
5    BLASTED   1 2 3 4                       Ready       1
7    HOTSTUF   7 8                           Blocked           1-1    I:932
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Blocked           PENDG

     FreeBlks: 17 18 19 20
     IOS                                 Execute Next
=================================== 850 ===================================

=================================== 900 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
5    BLASTED   1 2 3 4                       Blocked           1-2    I:941
7    HOTSTUF   7 8                           Blocked           1-1    I:932
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Executing                T:903

     FreeBlks: 17 18 19 20
=================================== 900 ===================================

=================================== 950 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
5    BLASTED   1 2 3 4                       Ready       2
7    HOTSTUF   7 8                           Ready       1
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Executing                T:953

     FreeBlks: 17 18 19 20
=================================== 950 ===================================

Completed: HOTSTUF at MC time: 959

De-Allocated: HOTSTUF at MC time 962
  Total Service Units: 340
  Total CPU Units    : 45
  MC Start Time      : 362
  MC End Time        : 959
  Total Elapsed Units: 597
  Memory Blks Used   :  7 8

Completed: BLASTED at MC time: 994

De-Allocated: BLASTED at MC time 997
  Total Service Units: 250
  Total CPU Units    : 90
  MC Start Time      : 341
  MC End Time        : 994
  Total Elapsed Units: 653
  Memory Blks Used   :  1 2 3 4

=================================== 1000 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Blocked           DONE

     FreeBlks: 1 2 3 4 7 8 17 18 19 20
     MASTER                              Execute Next
=================================== 1000 ===================================

Allocated: NONEMAN at MC time: 1001  (PID#: 9)
   Memory Block(s): 1 2 3 4 7 8 17 18

Started: NONEMAN at MC time: 1002

=================================== 1050 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   5 6 9 10 11 12 13 14 15 16    Blocked           1-2    I:1053
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1116

     FreeBlks: 19 20
     IDLE                                Execute Next
=================================== 1050 ===================================

Completed: HONEYDO at MC time: 1062

De-Allocated: HONEYDO at MC time 1065
  Total Service Units: 31
  Total CPU Units    : 115
  MC Start Time      : 746
  MC End Time        : 1062
  Total Elapsed Units: 316
  Memory Blks Used   :  5 6 9 10 11 12 13 14 15 16

=================================== 1100 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1116

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1100 ===================================

=================================== 1150 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1229

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1150 ===================================

=================================== 1200 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1229

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1200 ===================================

=================================== 1250 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1342

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1250 ===================================

=================================== 1300 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1342

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1300 ===================================

=================================== 1350 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Executing                T:1357

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
=================================== 1350 ===================================

=================================== 1400 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1455

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1400 ===================================

=================================== 1450 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1455

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1450 ===================================

=================================== 1500 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1568

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1500 ===================================

=================================== 1550 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 7 8 17 18             Blocked           1-1    I:1568

     FreeBlks: 5 6 9 10 11 12 13 14 15 16 19 20
     IDLE                                Execute Next
=================================== 1550 ===================================

Completed: NONEMAN at MC time: 1577

De-Allocated: NONEMAN at MC time 1580
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 1002
  MC End Time        : 1577
  Total Elapsed Units: 575
  Memory Blks Used   :  1 2 3 4 7 8 17 18

Ended O/S Simulation: 1. Last clock: 1582 


Starting O/S Simulation: 2. Version 5

O/S Parameters:

   Memory Model Used:      F
   Fixed Mem Blk Size:     5000
   Fixed Mem Blks Aval:    10
   Variable Mem Max Size:  0
   Variable Mem Tot Size:  0
   Max. Tasks Allowed:     10
   Process Mgmt Algthm:    FIFO   
   Initial Quantum Size:   10
   Number Disk Units:      3
   Number Tape Units:      3
   Number CD   Units:      3
   Print Every N Units:    50


Allocated: GOODPGM at MC time: 3  (PID#: 1)
   Memory Block(s): 1 2 3 4 5 6 7 8

Flushed: ARTSCLS from input queue - not enough memory!

Allocated: XOXOXOX at MC time: 3  (PID#: 2)
   Memory Block(s): 9 10

Started: GOODPGM at MC time: 4

Started: XOXOXOX at MC time: 19

=================================== 50 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Ready       1
2    XOXOXOX   9 10                          Blocked           PENDG

     FreeBlks:
     IOS                                 Execute Next
=================================== 50 ===================================

=================================== 100 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Ready       1
2    XOXOXOX   9 10                          Blocked           PENDG

     FreeBlks:
     IOS                                 Execute Next
=================================== 100 ===================================

Completed: XOXOXOX at MC time: 149

=================================== 150 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Ready       1
2    XOXOXOX   9 10                          Done

     FreeBlks:
     DONES                               Execute Next
=================================== 150 ===================================

De-Allocated: XOXOXOX at MC time 152
  Total Service Units: 35
  Total CPU Units    : 24
  MC Start Time      : 19
  MC End Time        : 149
  Total Elapsed Units: 130
  Memory Blks Used   :  9 10

Allocated: HOTSTUF at MC time: 156  (PID#: 3)
   Memory Block(s): 9 10

Started: HOTSTUF at MC time: 172

=================================== 200 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
1    GOODPGM   1 2 3 4 5 6 7 8               Executing                T:206
3    HOTSTUF   9 10                          Blocked           1-2    I:206

     FreeBlks:
=================================== 200 ===================================

Completed: GOODPGM at MC time: 241

De-Allocated: GOODPGM at MC time 244
  Total Service Units: 100
  Total CPU Units    : 52
  MC Start Time      : 4
  MC End Time        : 241
  Total Elapsed Units: 237
  Memory Blks Used   :  1 2 3 4 5 6 7 8

Allocated: WAYTOGO at MC time: 248  (PID#: 4)
   Memory Block(s): 1 2 3 4

Allocated: BARNONE at MC time: 248  (PID#: 5)
   Memory Block(s): 5 6 7 8

Started: WAYTOGO at MC time: 249

=================================== 250 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           DONE
4    WAYTOGO   1 2 3 4                       Executing                T:260
5    BARNONE   5 6 7 8                       Ready       1

     FreeBlks:
=================================== 250 ===================================

Started: BARNONE at MC time: 264

=================================== 300 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-3    I:393
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:363
5    BARNONE   5 6 7 8                       Blocked           1-2    I:328

     FreeBlks:
     IDLE                                Execute Next
=================================== 300 ===================================

=================================== 350 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-3    I:393
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:363
5    BARNONE   5 6 7 8                       Blocked           1-2    I:396

     FreeBlks:
     IDLE                                Execute Next
=================================== 350 ===================================

=================================== 400 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Held
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:476
5    BARNONE   5 6 7 8                       Ready       1

     FreeBlks:
     IOS                                 Execute Next
=================================== 400 ===================================

=================================== 450 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-2    I:511
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:476
5    BARNONE   5 6 7 8                       Blocked           1-3    I:484

     FreeBlks:
     IDLE                                Execute Next
=================================== 450 ===================================

=================================== 500 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-2    I:511
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:594
5    BARNONE   5 6 7 8                       Executing                T:506

     FreeBlks:
=================================== 500 ===================================

=================================== 550 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-2    I:624
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:594
5    BARNONE   5 6 7 8                       Blocked           1-3    I:559

     FreeBlks:
     IDLE                                Execute Next
=================================== 550 ===================================

=================================== 600 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
3    HOTSTUF   9 10                          Blocked           1-2    I:624
4    WAYTOGO   1 2 3 4                       Executing                T:609
5    BARNONE   5 6 7 8                       Blocked           1-3    I:635

     FreeBlks:
=================================== 600 ===================================

Completed: HOTSTUF at MC time: 633

De-Allocated: HOTSTUF at MC time 636
  Total Service Units: 340
  Total CPU Units    : 45
  MC Start Time      : 172
  MC End Time        : 633
  Total Elapsed Units: 461
  Memory Blks Used   :  9 10

=================================== 650 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:707
5    BARNONE   5 6 7 8                       Executing                T:657

     FreeBlks: 9 10
=================================== 650 ===================================

Completed: BARNONE at MC time: 662

De-Allocated: BARNONE at MC time 665
  Total Service Units: 250
  Total CPU Units    : 76
  MC Start Time      : 264
  MC End Time        : 662
  Total Elapsed Units: 398
  Memory Blks Used   :  5 6 7 8

Allocated: OVERDUE at MC time: 669  (PID#: 6)
   Memory Block(s): 5 6 7 8

Started: OVERDUE at MC time: 670

=================================== 700 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:707
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:779

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 700 ===================================

=================================== 750 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:820
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:779

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 750 ===================================

=================================== 800 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
4    WAYTOGO   1 2 3 4                       Blocked           1-1    I:820
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:892

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 800 ===================================

Completed: WAYTOGO at MC time: 829

De-Allocated: WAYTOGO at MC time 832
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 249
  MC End Time        : 829
  Total Elapsed Units: 580
  Memory Blks Used   :  1 2 3 4

Allocated: BLASTED at MC time: 836  (PID#: 7)
   Memory Block(s): 1 2 3 4

Started: BLASTED at MC time: 837

=================================== 850 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:892
7    BLASTED   1 2 3 4                       Executing                T:860

     FreeBlks: 9 10
=================================== 850 ===================================

=================================== 900 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Executing                T:907
7    BLASTED   1 2 3 4                       Blocked           1-1    I:908

     FreeBlks: 9 10
=================================== 900 ===================================

=================================== 950 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1005
7    BLASTED   1 2 3 4                       Blocked           1-1    I:983

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 950 ===================================

=================================== 1000 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1005
7    BLASTED   1 2 3 4                       Executing                T:1010

     FreeBlks: 9 10
=================================== 1000 ===================================

=================================== 1050 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1123
7    BLASTED   1 2 3 4                       Blocked           1-1    I:1058

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1050 ===================================

=================================== 1100 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1123
7    BLASTED   1 2 3 4                       Blocked           1-1    I:1133

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1100 ===================================

=================================== 1150 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1236
7    BLASTED   1 2 3 4                       Executing                T:1153

     FreeBlks: 9 10
=================================== 1150 ===================================

=================================== 1200 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Blocked           1-2    I:1236
7    BLASTED   1 2 3 4                       Blocked           1-1    I:1213

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1200 ===================================

Completed: BLASTED at MC time: 1234

De-Allocated: BLASTED at MC time 1237
  Total Service Units: 250
  Total CPU Units    : 90
  MC Start Time      : 837
  MC End Time        : 1234
  Total Elapsed Units: 397
  Memory Blks Used   :  1 2 3 4

=================================== 1250 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
6    OVERDUE   5 6 7 8                       Executing                T:1258

     FreeBlks: 1 2 3 4 9 10
=================================== 1250 ===================================

Completed: OVERDUE at MC time: 1252

De-Allocated: OVERDUE at MC time 1255
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 670
  MC End Time        : 1252
  Total Elapsed Units: 582
  Memory Blks Used   :  5 6 7 8

Allocated: HONEYDO at MC time: 1259  (PID#: 8)
   Memory Block(s): 1 2 3 4 5 6 7 8 9 10

Started: HONEYDO at MC time: 1260

=================================== 1300 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   1 2 3 4 5 6 7 8 9 10          Executing                T:1308

     FreeBlks:
=================================== 1300 ===================================

=================================== 1350 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   1 2 3 4 5 6 7 8 9 10          Executing                T:1354

     FreeBlks:
=================================== 1350 ===================================

=================================== 1400 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   1 2 3 4 5 6 7 8 9 10          Executing                T:1406

     FreeBlks:
=================================== 1400 ===================================

=================================== 1450 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
8    HONEYDO   1 2 3 4 5 6 7 8 9 10          Blocked           1-1    I:1451

     FreeBlks:
     IDLE                                Execute Next
=================================== 1450 ===================================

Completed: HONEYDO at MC time: 1460

De-Allocated: HONEYDO at MC time 1463
  Total Service Units: 31
  Total CPU Units    : 115
  MC Start Time      : 1260
  MC End Time        : 1460
  Total Elapsed Units: 200
  Memory Blks Used   :  1 2 3 4 5 6 7 8 9 10

Allocated: NONEMAN at MC time: 1467  (PID#: 9)
   Memory Block(s): 1 2 3 4 5 6 7 8

Started: NONEMAN at MC time: 1468

=================================== 1500 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1577

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1500 ===================================

=================================== 1550 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1577

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1550 ===================================

=================================== 1600 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1690

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1600 ===================================

=================================== 1650 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1690

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1650 ===================================

=================================== 1700 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Executing                T:1705

     FreeBlks: 9 10
     SC_INT                              Execute Next
=================================== 1700 ===================================

=================================== 1750 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1803

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1750 ===================================

=================================== 1800 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1803

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1800 ===================================

=================================== 1850 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1916

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1850 ===================================

=================================== 1900 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:1916

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1900 ===================================

=================================== 1950 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:2029

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 1950 ===================================

=================================== 2000 ===================================
Pid  Program                Memory           Current     Rdy   I/O    Event  
     Name                   Usage            State       List  T-Dv#  Info   
---  --------  ----------------------------  ----------  ----  -----  -------
9    NONEMAN   1 2 3 4 5 6 7 8               Blocked           1-1    I:2029

     FreeBlks: 9 10
     IDLE                                Execute Next
=================================== 2000 ===================================

Completed: NONEMAN at MC time: 2038

De-Allocated: NONEMAN at MC time 2041
  Total Service Units: 500
  Total CPU Units    : 30
  MC Start Time      : 1468
  MC End Time        : 2038
  Total Elapsed Units: 570
  Memory Blks Used   :  1 2 3 4 5 6 7 8

Ended O/S Simulation: 2. Last clock: 2043 
```
