; seahorn-benchmarks/./sv_comp_flat_small/ldv-linux-3.4-simple/32_1_cilled_true-unreach-call_ok_nondet_linux-3.4-32_1-drivers--input--touchscreen--mtouch.ko-ldv_main0_sequence_infinite_withcheck_stateful.cil.out.c.flat_000.smt2
(set-logic HORN)

(declare-fun |main_1| ( Int Bool Int ) Bool)

(assert
  (forall ( (A Bool) (B Int) (v_2 Int) ) 
    (=>
      (and
        (and true (= 0 v_2))
      )
      (main_1 v_2 A B)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) (L Bool) (M Int) (N Bool) (O Int) (P Bool) (Q Bool) (R Int) (S Bool) (T Int) (U Int) (V Int) (W Bool) (X Bool) (Y Bool) (Z Bool) (A1 Bool) (B1 Bool) (C1 Bool) (D1 Int) (E1 Int) (v_31 Int) (v_32 Int) ) 
    (=>
      (and
        (main_1 v_31 Q R)
        (and (= 0 v_31)
     (or (not Y) (not B1) (= L C1))
     (or (not Y) (not B1) (= E1 D1))
     (or (not Y) (not B1) (= D1 0))
     (or (not Y) (not B1) C1)
     (or P (not S) (not X))
     (or (not N) (not Z) (not W))
     (or (not W) (= N (= M 0)))
     (or (not W) (and S X))
     (or (not A1) (and Y B1))
     (or (not Y) (= K J))
     (or (not Y) (= J (+ 272 I)))
     (or (not Y) (= H G))
     (or (not Y) (= G (+ 272 F)))
     (or (not Y) (= D (+ 272 A)))
     (or (not Y) (= A V))
     (or (not Y) (= I T))
     (or (not Y) (= F U))
     (or (not Y) (= E D))
     (or (not Y) (= C B))
     (or (not Y) (= B (+ 40 A)))
     (or (not Y) (and Z W))
     (= A1 true)
     (= P (= O 0))
     (= 1 v_32))
      )
      (main_1 v_32 L E1)
    )
  )
)
(assert
  (forall ( (A Int) (B Bool) (C Int) (D Bool) (E Bool) (F Int) (G Bool) (H Bool) (I Bool) (J Bool) (K Bool) (L Bool) (M Bool) (N Bool) (O Bool) (P Bool) (v_16 Int) (v_17 Int) ) 
    (=>
      (and
        (main_1 v_16 E F)
        (and (= 0 v_16)
     (or (not L) (and G N) (and J M))
     (or (not G) D (not I))
     (or (not G) (not D) (not N))
     (or B (not K) (not H))
     (or (not H) (= B (= A 0)))
     (or (not H) (and G I))
     (or (not O) (and L P))
     (or (not J) (and K H))
     (= O true)
     (not L)
     (= D (= C 0))
     (= 2 v_17))
      )
      (main_1 v_17 E F)
    )
  )
)
(assert
  (forall ( (A Int) (B Bool) (C Bool) (D Bool) (E Bool) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) (L Int) (M Int) (N Int) (O Int) (P Int) (Q Int) (R Int) (S Int) (T Int) (U Int) (V Int) (W Int) (X Int) (Y Int) (Z Int) (A1 Int) (B1 Int) (C1 Int) (D1 Bool) (E1 Int) (F1 Bool) (G1 Bool) (H1 Bool) (I1 Int) (J1 Bool) (K1 Bool) (L1 Int) (M1 Int) (N1 Int) (O1 Bool) (P1 Int) (Q1 Int) (R1 Int) (S1 Int) (T1 Int) (U1 Bool) (V1 Int) (W1 Bool) (X1 Int) (Y1 Int) (Z1 Int) (A2 Int) (B2 Int) (C2 Int) (D2 Int) (E2 Int) (F2 Int) (G2 Int) (H2 Int) (I2 Int) (J2 Int) (K2 Int) (L2 Int) (M2 Int) (N2 Int) (O2 Int) (P2 Int) (Q2 Int) (R2 Int) (S2 Bool) (T2 Int) (U2 Int) (V2 Int) (W2 Int) (X2 Bool) (Y2 Bool) (Z2 Int) (A3 Int) (B3 Int) (C3 Int) (D3 Bool) (E3 Int) (F3 Bool) (G3 Int) (H3 Int) (I3 Int) (J3 Int) (K3 Int) (L3 Int) (M3 Int) (N3 Bool) (O3 Bool) (P3 Bool) (Q3 Bool) (R3 Bool) (S3 Bool) (T3 Int) (U3 Bool) (V3 Bool) (W3 Int) (X3 Int) (Y3 Int) (Z3 Bool) (A4 Bool) (B4 Bool) (C4 Bool) (D4 Bool) (E4 Bool) (F4 Int) (G4 Int) (H4 Int) (I4 Int) (J4 Bool) (K4 Bool) (L4 Bool) (M4 Bool) (N4 Bool) (O4 Bool) (P4 Int) (Q4 Bool) (R4 Bool) (S4 Bool) (T4 Bool) (U4 Bool) (V4 Bool) (W4 Bool) (X4 Bool) (Y4 Bool) (Z4 Bool) (A5 Bool) (B5 Bool) (C5 Bool) (D5 Bool) (E5 Int) (F5 Bool) (G5 Bool) (H5 Int) (I5 Bool) (J5 Bool) (K5 Bool) (L5 Int) (M5 Int) (N5 Int) (O5 Bool) (P5 Bool) (Q5 Bool) (R5 Bool) (S5 Bool) (T5 Bool) (U5 Bool) (V5 Bool) (W5 Bool) (X5 Int) (Y5 Int) (Z5 Bool) (A6 Bool) (B6 Int) (C6 Bool) (D6 Bool) (E6 Int) (F6 Bool) (G6 Bool) (H6 Bool) (I6 Bool) (J6 Bool) (K6 Int) (L6 Int) (M6 Bool) (N6 Bool) (O6 Bool) (P6 Bool) (Q6 Bool) (R6 Int) (S6 Int) (T6 Bool) (U6 Bool) (V6 Bool) (W6 Int) (X6 Bool) (Y6 Bool) (Z6 Bool) (A7 Bool) (B7 Bool) (C7 Bool) (D7 Bool) (E7 Bool) (F7 Bool) (G7 Bool) (H7 Bool) (I7 Bool) (J7 Int) (K7 Int) (L7 Int) (M7 Int) (N7 Int) (O7 Int) (P7 Int) (Q7 Int) (R7 Int) (S7 Int) (T7 Int) (U7 Int) (V7 Bool) (W7 Bool) (X7 Bool) (v_206 Int) (v_207 Int) ) 
    (=>
      (and
        (main_1 v_206 S3 T3)
        (let ((a!1 (or (not Y4) (= S2 (not (= R2 0)))))
      (a!2 (or (not Y4) (= Q2 (+ 16383 (* (- 1) P2)))))
      (a!3 (or (not D4) (= N3 (not (<= 0 I4)))))
      (a!4 (or (not Z3) (= P3 (not (<= 2 Y3))))))
  (and (= 1 v_206)
       (or (not X6)
           (and T6 G7)
           (and Z6 S4)
           (and A7 Q4)
           (and C7 Y4)
           (and D7 W4)
           (and F7 A5)
           (and H7 T5)
           (and I7 B4)
           (and E7 Q5)
           (and B7 U4)
           (and L4 Y6))
       (or (not O6) (and P6 H6) (and V5 Q6))
       (or (not H6) (and I6 F6) (and Z5 J6))
       (or (not Z5) (not J6) (= E1 L6))
       (or (not Z5) (not J6) (= L6 B6))
       (or (not Q5) (and I5 S5) (and O5 R5))
       (or (not I5) (and J5 F5) (and C5 K5))
       (or (not C5) (not K5) (= V1 0))
       (or (not C5) (not K5) (= M5 V1))
       (or (not L4) (not Y6) (= J7 T3))
       (or (not L4) (not Y6) (= U7 J7))
       (or Q3 (not U3) (not U5))
       (or (not Q3) (not U3) (not A4))
       (or P3 (not Z3) (not B5))
       (or (not P3) (not Z3) (not C4))
       (or O3 (not B4) (not E4))
       (or N3 (not D4) (not X4))
       (or (not N3) (not D4) (not K4))
       (or F3 (not J4) (not O4))
       (or (not F3) (not J4) (not M4))
       (or D3 (not N4) (not V4))
       (or (not D3) (not N4) (not R4))
       (or Y2 (not Q4) (not T4))
       (or X2 (not W4) (not Z4))
       (or W1 (not A5) (not D5))
       (or U1 (not C5) (not K5))
       (or (not U1) (not C5) (not G5))
       (or O1 (not I5) (not S5))
       (or (not O1) (not I5) (not P5))
       (or K1 (not T5) (not W5))
       (or (not D1) (not Z5) (not J6))
       (or D1 (not Z5) (not D6))
       (or E (not C6) (not N6))
       (or (not B7) (not U4) (= M7 T3))
       (or (not B7) (not U4) (= U7 M7))
       (or (not I6) (not F6) (= E1 K6))
       (or (not I6) (not F6) (= K6 E6))
       (or (not G6) (not E) (not C6))
       (or (not V5) (not Q6) (= I1 S6))
       (or (not V5) (not Q6) (= S6 (- 12)))
       (or (not V5) H1 (not Q6))
       (or (not V5) (not A6) (not H1))
       (or (not E7) (not Q5) (= U7 P7))
       (or (not E7) (not Q5) (= P7 0))
       (or (not U6) D (not O6))
       (or (not X7) (not X6) (= V3 V7))
       (or (not X7) (not X6) (= R3 V3))
       (or (not X7) (not X6) (= X3 W3))
       (or (not X7) (not X6) (= W3 U7))
       (or (not X7) (not C) (not X6))
       (or (not I7) (not B4) (= T7 T3))
       (or (not I7) (not B4) (= U7 T7))
       (or (not I7) (not O3) (not B4))
       (or (not H7) (not T5) (= S7 T3))
       (or (not H7) (not T5) (= U7 S7))
       (or (not H7) (not K1) (not T5))
       (or (not F7) (not A5) (= U7 Q7))
       (or (not F7) (not A5) (= Q7 T3))
       (or (not F7) (not W1) (not A5))
       (or (not D7) (not W4) (= O7 T3))
       (or (not D7) (not W4) (= U7 O7))
       (or (not D7) (not X2) (not W4))
       (or (not C7) (not Y4) (= N7 T3))
       (or (not C7) (not Y4) (= U7 N7))
       (or (not A7) (not Q4) (= U7 L7))
       (or (not A7) (not Q4) (= L7 T3))
       (or (not A7) (not Y2) (not Q4))
       (or (not Z6) (not S4) (= U7 K7))
       (or (not Z6) (not S4) (= K7 T3))
       (or (not T6) (and U6 O6) (and V6 M6))
       (or (not T6) (not G7) (= R7 W6))
       (or (not T6) (not G7) (= U7 R7))
       (or (not P6) (not H6) (= I1 R6))
       (or (not P6) (not H6) (= R6 E1))
       (or (not J5) (not F5) (= M5 L5))
       (or (not J5) (not F5) (= L5 H5))
       (or (not X6) (= C (and V7 B)))
       (or (not X6) (= B (= A 0)))
       (or (not X6) (= V7 (= U7 0)))
       (or (not O6) (= D (= I1 0)))
       (or (not M6) (and C6 N6))
       (or (not F6) (and G6 C6))
       (or (not C6) (= E (= E6 0)))
       (or (not C6) (and Z5 D6))
       (or (not Z5) (= D1 (= B6 0)))
       (or (not Z5) (= C1 B1))
       (or (not Z5) (= B1 (+ 88 M)))
       (or (not Z5) (= A1 Z))
       (or (not Z5) (= Z (+ 40 M)))
       (or (not Z5) (= Y X))
       (or (not Z5) (= X (+ 648 M)))
       (or (not Z5) (= W V))
       (or (not Z5) (= V (+ 30 M)))
       (or (not Z5) (= U T))
       (or (not Z5) (= T (+ 28 M)))
       (or (not Z5) (= S R))
       (or (not Z5) (= R (+ 26 M)))
       (or (not Z5) (= Q P))
       (or (not Z5) (= P (+ 24 M)))
       (or (not Z5) (= O N))
       (or (not Z5) (= N (+ 8 M)))
       (or (not Z5) (= M Y5))
       (or (not Z5) (= L Y5))
       (or (not Z5) (= K J))
       (or (not Z5) (= J (+ 36 F)))
       (or (not Z5) (= I X5))
       (or (not Z5) (= H G))
       (or (not Z5) (= G (+ 8 F)))
       (or (not Z5) (= F X5))
       (or (not Z5) (and V5 A6))
       (or (not T5) (= K1 (and J1 S3)))
       (or (not T5) (= J1 (= Y3 0)))
       (or (not T5) (and U3 U5))
       (or (not O5) (= N1 M1))
       (or (not O5) (= M1 (+ 648 L1)))
       (or (not O5) (= L1 N5))
       (or (not O5) (and I5 P5))
       (or (not I5) (= O1 (= N5 0)))
       (or (not F5) (= R1 Q1))
       (or (not F5) (= Q1 (+ 648 P1)))
       (or (not F5) (= P1 E5))
       (or (not F5) (and C5 G5))
       (or (not C5) (= U1 (= E5 0)))
       (or (not C5) (= T1 S1))
       (or (not C5) (and A5 D5))
       (or (not A5) (= W1 (= T3 1)))
       (or (not A5) (and Z3 B5))
       a!1
       (or (not Y4) (= T2 (ite S2 1 0)))
       a!2
       (or (not Y4) (= O2 (* 128 N2)))
       (or (not Y4) (= N2 M2))
       (or (not Y4) (= L2 K2))
       (or (not Y4) (= K2 (+ 24 G4)))
       (or (not Y4) (= J2 I2))
       (or (not Y4) (= H2 G2))
       (or (not Y4) (= G2 (+ 23 G4)))
       (or (not Y4) (= F2 (* 128 E2)))
       (or (not Y4) (= E2 D2))
       (or (not Y4) (= C2 B2))
       (or (not Y4) (= B2 (+ 22 G4)))
       (or (not Y4) (= A2 Z1))
       (or (not Y4) (= Y1 X1))
       (or (not Y4) (= X1 (+ 21 G4)))
       (or (not Y4) (and W4 Z4))
       (or (not W4) (= X2 (= W2 5)))
       (or (not W4) (= W2 (+ 1 V2)))
       (or (not W4) (= U2 F4))
       (or (not W4) (and D4 X4))
       (or (not U4) (and N4 V4))
       (or (not S4) (and Q4 T4))
       (or (not Q4) (= Y2 (= P4 16)))
       (or (not Q4) (and N4 R4))
       (or (not N4) (= D3 (= C3 13)))
       (or (not N4) (= P4 (+ 1 Z2)))
       (or (not N4) (= B3 A3))
       (or (not N4) (= A3 (+ H4 Z2)))
       (or (not N4) (and J4 O4))
       (or (not L4) (= E3 I4))
       (or (not L4) (and J4 M4))
       (or (not J4) (= F3 (= I4 1)))
       (or (not J4) (and D4 K4))
       a!3
       (or (not D4) (= H4 (+ 20 G4)))
       (or (not D4) (= G4 F4))
       (or (not D4) (= M3 H4))
       (or (not D4) (= L3 K3))
       (or (not D4) (= K3 (+ J3 G4)))
       (or (not D4) (= J3 (+ 20 I3)))
       (or (not D4) (= H3 G3))
       (or (not D4) (= G3 (+ 16 G4)))
       (or (not D4) (and B4 E4))
       (or (not B4) (= O3 (= Y3 2)))
       (or (not B4) (and Z3 C4))
       a!4
       (or (not Z3) (and U3 A4))
       (or (not V5) (= H1 (or F1 G1)))
       (or (not V5) (= G1 (= Y5 0)))
       (or (not V5) (= F1 (= X5 0)))
       (or (not V5) (and T5 W5))
       (or (not W7) (and X7 X6))
       (or (not T6) (= W6 (+ 1 T3)))
       (= W7 true)
       (= Q3 (not (<= 1 Y3)))
       (= 1 v_207)))
      )
      (main_1 v_207 R3 X3)
    )
  )
)
(assert
  (forall ( (A Int) (B Bool) (C Bool) (D Bool) (E Bool) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) (L Int) (M Int) (N Int) (O Int) (P Int) (Q Int) (R Int) (S Int) (T Int) (U Int) (V Int) (W Int) (X Int) (Y Int) (Z Int) (A1 Int) (B1 Int) (C1 Int) (D1 Bool) (E1 Int) (F1 Bool) (G1 Bool) (H1 Bool) (I1 Int) (J1 Bool) (K1 Bool) (L1 Int) (M1 Int) (N1 Int) (O1 Bool) (P1 Int) (Q1 Int) (R1 Int) (S1 Int) (T1 Int) (U1 Bool) (V1 Int) (W1 Bool) (X1 Int) (Y1 Int) (Z1 Int) (A2 Int) (B2 Int) (C2 Int) (D2 Int) (E2 Int) (F2 Int) (G2 Int) (H2 Int) (I2 Int) (J2 Int) (K2 Int) (L2 Int) (M2 Int) (N2 Int) (O2 Int) (P2 Int) (Q2 Int) (R2 Int) (S2 Bool) (T2 Int) (U2 Int) (V2 Int) (W2 Int) (X2 Bool) (Y2 Bool) (Z2 Int) (A3 Int) (B3 Int) (C3 Int) (D3 Bool) (E3 Int) (F3 Bool) (G3 Int) (H3 Int) (I3 Int) (J3 Int) (K3 Int) (L3 Int) (M3 Int) (N3 Bool) (O3 Bool) (P3 Bool) (Q3 Bool) (R3 Bool) (S3 Int) (T3 Bool) (U3 Bool) (V3 Bool) (W3 Bool) (X3 Bool) (Y3 Bool) (Z3 Int) (A4 Bool) (B4 Bool) (C4 Bool) (D4 Bool) (E4 Bool) (F4 Bool) (G4 Int) (H4 Int) (I4 Int) (J4 Int) (K4 Bool) (L4 Bool) (M4 Bool) (N4 Bool) (O4 Bool) (P4 Bool) (Q4 Int) (R4 Bool) (S4 Bool) (T4 Bool) (U4 Bool) (V4 Bool) (W4 Bool) (X4 Bool) (Y4 Bool) (Z4 Bool) (A5 Bool) (B5 Bool) (C5 Bool) (D5 Bool) (E5 Bool) (F5 Int) (G5 Bool) (H5 Bool) (I5 Int) (J5 Bool) (K5 Bool) (L5 Bool) (M5 Int) (N5 Int) (O5 Int) (P5 Bool) (Q5 Bool) (R5 Bool) (S5 Bool) (T5 Bool) (U5 Bool) (V5 Bool) (W5 Bool) (X5 Bool) (Y5 Int) (Z5 Int) (A6 Bool) (B6 Bool) (C6 Int) (D6 Bool) (E6 Bool) (F6 Int) (G6 Bool) (H6 Bool) (I6 Bool) (J6 Bool) (K6 Bool) (L6 Int) (M6 Int) (N6 Bool) (O6 Bool) (P6 Bool) (Q6 Bool) (R6 Bool) (S6 Int) (T6 Int) (U6 Bool) (V6 Bool) (W6 Bool) (X6 Int) (Y6 Bool) (Z6 Bool) (A7 Bool) (B7 Bool) (C7 Bool) (D7 Bool) (E7 Bool) (F7 Bool) (G7 Bool) (H7 Bool) (I7 Bool) (J7 Bool) (K7 Int) (L7 Int) (M7 Int) (N7 Int) (O7 Int) (P7 Int) (Q7 Int) (R7 Int) (S7 Int) (T7 Int) (U7 Int) (V7 Int) (W7 Bool) (X7 Bool) (Y7 Bool) (Z7 Bool) (A8 Bool) (v_209 Int) (v_210 Int) ) 
    (=>
      (and
        (main_1 v_209 R3 S3)
        (let ((a!1 (or (not A4) (= P3 (not (<= 2 Z3)))))
      (a!2 (or (not Z4) (= S2 (not (= R2 0)))))
      (a!3 (or (not Z4) (= Q2 (+ 16383 (* (- 1) P2)))))
      (a!4 (or (not E4) (= N3 (not (<= 0 J4))))))
  (and (= 1 v_209)
       (or (not Y6)
           (and U6 H7)
           (and Z6 M4)
           (and C7 V4)
           (and D7 Z4)
           (and F7 R5)
           (and G7 B5)
           (and I7 U5)
           (and J7 C4)
           (and E7 X4)
           (and R4 B7)
           (and T4 A7))
       (or (not P6) (and W5 R6) (and I6 Q6))
       (or (not K6) (not A6) (= E1 M6))
       (or (not K6) (not A6) (= M6 C6))
       (or (not K6) (not D1) (not A6))
       (or (not I6) (and J6 G6) (and K6 A6))
       (or (not I6) (not Q6) (= I1 S6))
       (or (not I6) (not Q6) (= S6 E1))
       (or (not W5) (not H1) (not B6))
       (or (not W5) (not R6) (= I1 T6))
       (or (not W5) (not R6) (= T6 (- 12)))
       (or (not W5) (not R6) H1)
       (or (not R5) (and J5 T5) (and S5 P5))
       (or (not J5) (and D5 L5) (and G5 K5))
       (or (not J5) (not O1) (not Q5))
       (or (not J5) (not T5) O1)
       (or (not G5) (not K5) (= M5 I5))
       (or (not G5) (not K5) (= N5 M5))
       (or (not D5) (not U1) (not H5))
       (or (not D5) (not L5) (= V1 0))
       (or (not D5) (not L5) (= N5 V1))
       (or (not D5) (not L5) U1)
       (or (not C5) P3 (not A4))
       (or (not B5) (not E5) W1)
       (or (not X4) (not A5) X2)
       (or (not T4) (not A7) (= V7 L7))
       (or (not T4) (not A7) (= L7 S3))
       (or (not R4) (not B7) (= V7 M7))
       (or (not R4) (not B7) (= M7 S3))
       (or (not R4) (not B7) (not Y2))
       (or (not R4) (not U4) Y2)
       (or (not P4) F3 (not K4))
       (or (not O4) (not D3) (not S4))
       (or (not O4) (not W4) D3)
       (or (not N4) (not F3) (not K4))
       (or (not E4) (not N3) (not L4))
       (or (not E4) (not Y4) N3)
       (or (not D4) (not P3) (not A4))
       (or (not C4) (not F4) O3)
       (or (not Q3) (not T3) (not B4))
       (or Q3 (not T3) (not V5))
       (or K1 (not U5) (not X5))
       (or (not E7) (not X4) (= V7 P7))
       (or (not E7) (not X4) (= P7 S3))
       (or (not E7) (not X4) (not X2))
       (or (not J6) (not G6) (= E1 L6))
       (or (not J6) (not G6) (= L6 F6))
       (or (not E6) D1 (not A6))
       (or (not D6) E (not O6))
       (or (not D6) (not E) (not H6))
       (or (not Y7) (not P6) (not D))
       (or (not X7) (and Z7 Y6) (and Y7 P6))
       (or (not Z7) (not Y6) C)
       (or (not J7) (not C4) (= V7 U7))
       (or (not J7) (not C4) (= U7 S3))
       (or (not J7) (not C4) (not O3))
       (or (not I7) (not U5) (= V7 T7))
       (or (not I7) (not U5) (= T7 S3))
       (or (not I7) (not K1) (not U5))
       (or (not G7) (not B5) (= V7 R7))
       (or (not G7) (not B5) (= R7 S3))
       (or (not G7) (not B5) (not W1))
       (or (not F7) (not R5) (= V7 Q7))
       (or (not F7) (not R5) (= Q7 0))
       (or (not D7) (not Z4) (= V7 O7))
       (or (not D7) (not Z4) (= O7 S3))
       (or (not C7) (not V4) (= V7 N7))
       (or (not C7) (not V4) (= N7 S3))
       (or (not Z6) (not M4) (= V7 K7))
       (or (not Z6) (not M4) (= K7 S3))
       (or (not V6) (not P6) D)
       (or (not U6) (and V6 P6) (and W6 N6))
       (or (not U6) (not H7) (= V7 S7))
       (or (not U6) (not H7) (= S7 X6))
       (or (not N6) (and D6 O6))
       (or (not A6) (= D1 (= C6 0)))
       (or (not A6) (= H G))
       (or (not A6) (= G (+ 8 F)))
       (or (not A6) (= F Y5))
       (or (not A6) (= C1 B1))
       (or (not A6) (= B1 (+ 88 M)))
       (or (not A6) (= A1 Z))
       (or (not A6) (= Z (+ 40 M)))
       (or (not A6) (= Y X))
       (or (not A6) (= X (+ 648 M)))
       (or (not A6) (= W V))
       (or (not A6) (= V (+ 30 M)))
       (or (not A6) (= U T))
       (or (not A6) (= T (+ 28 M)))
       (or (not A6) (= S R))
       (or (not A6) (= R (+ 26 M)))
       (or (not A6) (= Q P))
       (or (not A6) (= P (+ 24 M)))
       (or (not A6) (= O N))
       (or (not A6) (= N (+ 8 M)))
       (or (not A6) (= M Z5))
       (or (not A6) (= L Z5))
       (or (not A6) (= K J))
       (or (not A6) (= J (+ 36 F)))
       (or (not A6) (= I Y5))
       (or (not A6) (and W5 B6))
       (or (not P5) (= N1 M1))
       (or (not P5) (= M1 (+ 648 L1)))
       (or (not P5) (= L1 O5))
       (or (not P5) (and J5 Q5))
       (or (not K4) (= F3 (= J4 1)))
       (or (not K4) (and E4 L4))
       a!1
       (or (not A4) (and T3 B4))
       (or (not P6) (= D (= I1 0)))
       (or (not G6) (and D6 H6))
       (or (not W5) (= H1 (or G1 F1)))
       (or (not W5) (= F1 (= Y5 0)))
       (or (not W5) (= G1 (= Z5 0)))
       (or (not W5) (and U5 X5))
       (or (not U5) (= K1 (and J1 R3)))
       (or (not U5) (= J1 (= Z3 0)))
       (or (not U5) (and T3 V5))
       (or (not J5) (= O1 (= O5 0)))
       (or (not G5) (= R1 Q1))
       (or (not G5) (= Q1 (+ 648 P1)))
       (or (not G5) (= P1 F5))
       (or (not G5) (and D5 H5))
       (or (not D5) (= U1 (= F5 0)))
       (or (not D5) (= T1 S1))
       (or (not D5) (and B5 E5))
       (or (not B5) (= W1 (= S3 1)))
       (or (not B5) (and C5 A4))
       a!2
       (or (not Z4) (= X1 (+ 21 H4)))
       (or (not Z4) (= T2 (ite S2 1 0)))
       a!3
       (or (not Z4) (= O2 (* 128 N2)))
       (or (not Z4) (= N2 M2))
       (or (not Z4) (= L2 K2))
       (or (not Z4) (= K2 (+ 24 H4)))
       (or (not Z4) (= J2 I2))
       (or (not Z4) (= H2 G2))
       (or (not Z4) (= G2 (+ 23 H4)))
       (or (not Z4) (= F2 (* 128 E2)))
       (or (not Z4) (= E2 D2))
       (or (not Z4) (= C2 B2))
       (or (not Z4) (= B2 (+ 22 H4)))
       (or (not Z4) (= A2 Z1))
       (or (not Z4) (= Y1 X1))
       (or (not Z4) (and X4 A5))
       (or (not X4) (= X2 (= W2 5)))
       (or (not X4) (= W2 (+ 1 V2)))
       (or (not X4) (= U2 G4))
       (or (not X4) (and E4 Y4))
       (or (not V4) (and O4 W4))
       (or (not T4) (and R4 U4))
       (or (not R4) (= Y2 (= Q4 16)))
       (or (not R4) (and O4 S4))
       (or (not O4) (= D3 (= C3 13)))
       (or (not O4) (= Q4 (+ 1 Z2)))
       (or (not O4) (= B3 A3))
       (or (not O4) (= A3 (+ I4 Z2)))
       (or (not O4) (and P4 K4))
       (or (not M4) (= E3 J4))
       (or (not M4) (and N4 K4))
       a!4
       (or (not E4) (= H4 G4))
       (or (not E4) (= G3 (+ 16 H4)))
       (or (not E4) (= I4 (+ 20 H4)))
       (or (not E4) (= M3 I4))
       (or (not E4) (= L3 K3))
       (or (not E4) (= K3 (+ J3 H4)))
       (or (not E4) (= J3 (+ 20 I3)))
       (or (not E4) (= H3 G3))
       (or (not E4) (and C4 F4))
       (or (not C4) (= O3 (= Z3 2)))
       (or (not C4) (and D4 A4))
       (or (not X3) (and V3 Y3))
       (or (not V3) (and U3 W3))
       (or (not U3) (and A8 X7))
       (or (not Y6) (= C (and W7 B)))
       (or (not Y6) (= B (= A 0)))
       (or (not Y6) (= W7 (= V7 0)))
       (or (not D6) (= E (= F6 0)))
       (or (not D6) (and E6 A6))
       (or (not U6) (= X6 (+ 1 S3)))
       (= X3 true)
       (not V3)
       (= Q3 (not (<= 1 Z3)))
       (= 2 v_210)))
      )
      (main_1 v_210 R3 S3)
    )
  )
)
(assert
  (forall ( (A Bool) (B Int) (v_2 Int) ) 
    (=>
      (and
        (main_1 v_2 A B)
        (= 2 v_2)
      )
      false
    )
  )
)

(check-sat)
(exit)
