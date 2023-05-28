#!/usr/bin/env bash

./hw3 < t1.in > t1.my
diff t1.in.out t1.my

./hw3 < t2.in > t2.my
diff t2.in.out t2.my

./hw3 < t03.in > t3.my
diff t03.in.out t3.my

./hw3 < t05-bare-block.in > t5.my
diff t05-bare-block.in.out t5.my

./hw3 < t06-del-block.in > t6.my
diff t06-del-block.in.out t6.my

./hw3 < t07-alt-proto-mismatch.in > t7.my
diff t07-alt-proto-mismatch.in.out t7.my

./hw3 < t08-redeclaration.in > t8.my
diff t08-redeclaration.in.out t8.my

./hw3 < t09-while.in > t9.my
diff t09-while.in.out t9.my

./hw3 < t10-print.in > t10.my
diff t10-print.in.out t10.my

./hw3 < t12-mainmissing.in > t12.my
diff t12-mainmissing.in.out t12.my

./hw3 < t13-main-not-void.in > t13.my
diff t13-main-not-void.in.out t13.my

./hw3 < t14-main-redef.in > t14.my
diff t14-main-redef.in.out t14.my

./hw3 < t15-main-no-params.in > t15.my
diff t15-main-no-params.in.out t15.my

./hw3 < t16-nested-return.in > t16.my
diff t16-nested-return.in.out t16.my

./hw3 < t17-definition-orders.in > t17.my
diff t17-definition-orders.in.out t17.my

./hw3 < t18-formal-redeclaration.in > t18.my
diff t18-formal-redeclaration.in.out t18.my

./hw3 < t19-redeclare-over-formal.in > t19.my
diff t19-redeclare-over-formal.in.out t19.my

./hw3 < t21-byte-sizing.in > t21.my
diff t21-byte-sizing.in.out t21.my

./hw3 < t22-typed-init.in > t22.my
diff t22-typed-init.in.out t22.my

./hw3 < t23-while-fail.in > t23.my
diff t23-while-fail.in.out t23.my

./hw3 < t24-stress-math.in > t24.my
diff t24-stress-math.in.out t24.my

./hw3 < t25.in > t25.my
diff t25.in.out t25.my

./hw3 < t26.in > t26.my
diff t26.in.out t26.my

./hw3 < t_exp.in > t_exp.my
diff t_exp.in.out t_exp.my

./hw3 < tj1.in > tj1.my
diff tj1.in.out tj1.my

./hw3 < tj2.in > tj2.my
diff tj2.in.out tj2.my

./hw3 < tj3.in > tj3.my
diff tj3.in.out tj3.my

./hw3 < tj4.in > tj4.my
diff tj4.in.out tj4.my

./hw3 < tj5.in > tj5.my
diff tj5.in.out tj5.my

./hw3 < tj6.in > tj6.my
diff tj6.in.out tj6.my

./hw3 < tj7.in > tj7.my
diff tj7.in.out tj7.my

./hw3 < tj8.in > tj8.my
diff tj8.in.out tj8.my

./hw3 < tj9.in > tj9.my
diff tj9.in.out tj9.my

./hw3 < tj10.in > tj10.my
diff tj10.in.out tj10.my

./hw3 < tj11.in > tj11.my
diff tj11.in.out tj11.my

./hw3 < tj12.in > tj12.my
diff tj12.in.out tj12.my

./hw3 < tj13.in > tj13.my
diff tj13.in.out tj13.my