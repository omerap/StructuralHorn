; ./eldarica-misc/./LIA/Consistency/delauny-edge-flipping.7_000.smt2
(set-logic HORN)

(declare-fun |combined_incircle| ( Int Int Int Int Int Int Int Int Int Int Int ) Bool)
(declare-fun |CHC_COMP_FALSE| ( ) Bool)
(declare-fun |step_incircle| ( Int Int Int Int Int Int Int Int Int Int Int ) Bool)
(declare-fun |incircle| ( Int Int Int Int Int Int Int Int Int Int Int ) Bool)

(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (and (>= (+ (* (- 1) E) I) 0)
     (>= (+ (* (- 1) E) H) 0)
     (>= (+ (* (- 1) E) G) 0)
     (>= (+ (* (- 1) E) F) 3)
     (>= (+ (* (- 1) E) D) 0)
     (>= (+ (* (- 1) E) C) 0)
     (>= (+ (* (- 1) E) B) 0)
     (>= (+ (* (- 1) E) A) 0)
     (>= (+ F (* (- 1) J)) 0)
     (>= (+ F (* (- 1) I)) 0)
     (>= (+ F (* (- 1) H)) 0)
     (>= (+ F (* (- 1) G)) 0)
     (>= (+ F (* (- 1) D)) 0)
     (>= (+ F (* (- 1) C)) 0)
     (>= (+ F (* (- 1) B)) 0)
     (>= (+ F (* (- 1) A)) 0)
     (>= (+ (* (- 1) E) J) 0))
      )
      (incircle A B C D E F G H I J K)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (and (>= (+ (* (- 1) E) I) 0)
     (>= (+ (* (- 1) E) H) 0)
     (>= (+ (* (- 1) E) G) 0)
     (>= (+ (* (- 1) E) F) 3)
     (>= (+ (* (- 1) E) D) 0)
     (>= (+ (* (- 1) E) C) 0)
     (>= (+ (* (- 1) E) B) 0)
     (>= (+ (* (- 1) E) A) 0)
     (>= (+ (* (- 1) D) G) 0)
     (>= (+ (* (- 1) C) J) 0)
     (>= (+ (* (- 1) B) H) 0)
     (>= (+ (* (- 1) A) I) 0)
     (>= (+ F (* (- 1) J)) 0)
     (>= (+ F (* (- 1) I)) 0)
     (>= (+ F (* (- 1) H)) 0)
     (>= (+ F (* (- 1) G)) 0)
     (>= (+ F (* (- 1) D)) 0)
     (>= (+ F (* (- 1) C)) 0)
     (>= (+ F (* (- 1) B)) 0)
     (>= (+ F (* (- 1) A)) 0)
     (>= (+ D (* (- 1) G)) 0)
     (>= (+ C (* (- 1) J)) 0)
     (>= (+ B (* (- 1) H)) 0)
     (>= (+ A (* (- 1) I)) 0)
     (>= (+ (* (- 1) E) J) 0))
      )
      (step_incircle A B C D E F G H I J K)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (incircle A B C D E F G H I J K)
        true
      )
      (combined_incircle A B C D E F G H I J K)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (step_incircle A B C D E F G H I J K)
        true
      )
      (combined_incircle A B C D E F G H I J K)
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (combined_incircle A B C D E F K J I H G)
        (step_incircle A B C D E F H J I K G)
        true
      )
      CHC_COMP_FALSE
    )
  )
)
(assert
  (forall ( (A Int) (B Int) (C Int) (D Int) (E Int) (F Int) (G Int) (H Int) (I Int) (J Int) (K Int) ) 
    (=>
      (and
        (step_incircle A B C D E F K J I H G)
        (combined_incircle A B C D E F H J I K G)
        true
      )
      CHC_COMP_FALSE
    )
  )
)
(assert
  (forall ( (CHC_COMP_UNUSED Bool) ) 
    (=>
      (and
        CHC_COMP_FALSE
      )
      false
    )
  )
)

(check-sat)
(exit)
