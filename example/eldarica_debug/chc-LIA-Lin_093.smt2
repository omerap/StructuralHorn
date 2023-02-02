; seahorn-benchmarks/./sv_comp_flat_small/termination-crafted-lit/ChenFlurMukhopadhyay-SAS2012-Ex2.06_false-termination.c.flat_000.smt2
(set-logic HORN)

(declare-fun |main_1| ( Int Int Int Int ) Bool)

(assert
  (forall ( (A Int) (B Int) (C Int) (v_3 Int) ) 
    (=>
      (and
        (and true (= 0 v_3))
      )
      (main_1 v_3 A B C)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Bool) (F Int) (G Int) (H Int) (I Bool) (J Int) (K Int) (L Int) (M Bool) (N Bool) (O Bool) (P Bool) (Q Int) (R Int) (S Int) (v_19 Int) (v_20 Int) ) 
    (=>
      (and
        (main_1 v_19 F G H)
        (and (= 0 v_19)
     (= L (* 4 J))
     (= D (+ L K))
     (or (not M) (not P) (= C S))
     (or (not M) (not P) (= B R))
     (or (not M) (not P) (= A Q))
     (or (not M) (not P) (= S J))
     (or (not M) (not P) (= R K))
     (or (not M) (not P) (= Q L))
     (or E (not I) (not N))
     (or (not O) (and M P))
     (or (not M) (and I N))
     (= O true)
     (= E (not (<= D 0)))
     (= 1 v_20))
      )
      (main_1 v_20 B C A)
    )
  )
)
(assert
  (forall ( (A Int) (B Bool) (C Int) (D Int) (E Int) (F Bool) (G Int) (H Int) (I Int) (J Bool) (K Bool) (v_11 Int) (v_12 Int) ) 
    (=>
      (and
        (main_1 v_11 C D E)
        (and (= 0 v_11)
     (= A (+ I H))
     (= I (* 4 G))
     (or (not F) (not B) (not K))
     (or (not J) (and F K))
     (= J true)
     (= B (not (<= A 0)))
     (= 2 v_12))
      )
      (main_1 v_12 C D E)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Bool) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Bool) (L Int) (M Int) (N Int) (O Int) (P Int) (Q Bool) (R Bool) (v_18 Int) (v_19 Int) ) 
    (=>
      (and
        (main_1 v_18 H I J)
        (and (= 1 v_18)
     (= O (+ A B))
     (= C (+ P J))
     (= B (* (- 2) I))
     (= A (* 4 H))
     (= P (* 4 O))
     (or (not R) (not K) (= M L))
     (or (not R) (not K) (= N O))
     (or (not R) (not K) (= L P))
     (or (not R) (not K) (= G N))
     (or (not R) (not K) (= F M))
     (or (not R) (not K) (= E L))
     (or D (not R) (not K))
     (or (not Q) (and R K))
     (= Q true)
     (= D (not (<= C 0)))
     (= 1 v_19))
      )
      (main_1 v_19 F G E)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Bool) (E Int) (F Int) (G Int) (H Bool) (I Bool) (J Int) (K Int) (L Bool) (M Bool) (N Bool) (v_14 Int) (v_15 Int) ) 
    (=>
      (and
        (main_1 v_14 E F G)
        (and (= 1 v_14)
     (= K (* 4 J))
     (= J (+ A B))
     (= C (+ K G))
     (= B (* (- 2) F))
     (= A (* 4 E))
     (or (not D) (not H) (not M))
     (or (not L) (and H M))
     (or (not I) (and N L))
     (= I true)
     (= D (not (<= C 0)))
     (= 2 v_15))
      )
      (main_1 v_15 E F G)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (v_3 Int) ) 
    (=>
      (and
        (main_1 v_3 A B C)
        (= 2 v_3)
      )
      false
    )
  )
)

(check-sat)
(exit)
