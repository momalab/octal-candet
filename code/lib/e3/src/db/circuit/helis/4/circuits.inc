template<> void $NameUint<4>::d_add
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n12 = gate_and(b[0], a[0]);
  auto n11 = gate_xor(b[1], a[1]);
  y[1] = gate_xor(n12, n11);
  auto n16 = gate_xor(b[2], a[2]);
  auto n14 = gate_nand(b[1], a[1]);
  auto n13 = gate_nand(n12, n11);
  auto n15 = gate_nand(n14, n13);
  y[2] = gate_xor(n16, n15);
  auto n18 = gate_nand(n16, n15);
  auto n17 = gate_nand(b[2], a[2]);
  auto n19 = gate_nand(n18, n17);
  auto n20 = gate_xnor(n19, b[3]);
  y[3] = gate_xnor(a[3], n20);
  auto _add_x_1_n12 = gate_xor(b[0], a[0]);
  y[0] = gate_buf(_add_x_1_n12);
}
template<> void $NameUint<4>::d_bitand
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[3] = gate_and(b[3], a[3]);
  y[2] = gate_and(b[2], a[2]);
  y[1] = gate_and(b[1], a[1]);
  y[0] = gate_and(b[0], a[0]);
}
template<> void $NameUint<4>::d_bitnot
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  y[3] = gate_not(a[3]);
  y[2] = gate_not(a[2]);
  y[1] = gate_not(a[1]);
  y[0] = gate_not(a[0]);
}
template<> void $NameUint<4>::d_bitor
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[3] = gate_or(a[3], b[3]);
  y[2] = gate_or(a[2], b[2]);
  y[1] = gate_or(a[1], b[1]);
  y[0] = gate_or(a[0], b[0]);
}
template<> void $NameUint<4>::d_bitsum
(vector<Bit> & y, const vector<Bit> & a, const Bit & zero) noexcept
{
  y[3] = gate_buf(zero);
  auto N0 = gate_buf(a[0]);
  auto n9 = gate_nand(a[1], a[2]);
  auto n11 = gate_nand(N0, a[3]);
  y[2] = gate_nor(n9, n11);
  auto n13 = gate_xor(a[1], a[2]);
  auto n12 = gate_xor(N0, a[3]);
  auto n8 = gate_nand(n13, n12);
  auto n10 = gate_nand(n11, n8);
  y[1] = gate_mux(n11, n10, n9);
  y[0] = gate_xor(n13, n12);
}
template<> void $NameUint<4>::d_bitxor
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[3] = gate_xor(b[3], a[3]);
  y[2] = gate_xor(b[2], a[2]);
  y[1] = gate_xor(b[1], a[1]);
  y[0] = gate_xor(b[0], a[0]);
}
template<> void $NameUint<4>::d_boolmul
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[0] = gate_and(a[0], b[0]);
  y[1] = gate_and(a[0], b[1]);
  y[2] = gate_and(a[0], b[2]);
  y[3] = gate_and(a[0], b[3]);
}
template<> void $NameUint<4>::d_boolmux
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b, const vector<Bit> & c) noexcept
{
  y[0] = gate_mux(c[0], b[0], a[0]);
  y[1] = gate_mux(c[1], b[1], a[0]);
  y[2] = gate_mux(c[2], b[2], a[0]);
  y[3] = gate_mux(c[3], b[3], a[0]);
}
template<> void $NameUint<4>::d_carryadd
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n10 = gate_xor(b[1], a[1]);
  auto n9 = gate_and(b[0], a[0]);
  y[1] = gate_xor(n10, n9);
  auto n12 = gate_nand(b[1], a[1]);
  auto n11 = gate_nand(n10, n9);
  auto n13 = gate_nand(n12, n11);
  auto n14 = gate_xor(b[2], a[2]);
  y[2] = gate_xor(n13, n14);
  auto _add_x_1_n12 = gate_xor(b[0], a[0]);
  auto n16 = gate_nand(b[2], a[2]);
  auto n15 = gate_nand(n14, n13);
  auto _add_x_1_n14 = gate_nand(n16, n15);
  y[3] = gate_buf(_add_x_1_n14);
  y[0] = gate_buf(_add_x_1_n12);
}
template<> void $NameUint<4>::d_dec
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  y[1] = gate_xnor(a[0], a[1]);
  y[0] = gate_not(a[0]);
  auto n4 = gate_or(a[0], a[1]);
  auto n3 = gate_or(a[2], n4);
  y[3] = gate_xnor(a[3], n3);
  y[2] = gate_xnor(a[2], n4);
}
template<> void $NameUint<4>::d_div
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n25 = gate_xnor(b[0], b[1]);
  auto n45 = gate_not(a[2]);
  auto n28 = gate_nand(n45, b[0]);
  auto n72 = gate_not(a[3]);
  auto n13 = gate_nand(n72, b[1]);
  auto n14 = gate_and(n28, n13);
  auto n15 = gate_not(b[0]);
  auto n24 = gate_nor(n15, a[0]);
  auto n18 = gate_nand(b[2], b[1]);
  auto n59 = gate_nand(b[0], b[1]);
  auto n67 = gate_and(n18, n59);
  auto n19 = gate_not(n67);
  auto n23 = gate_nor(n25, a[1]);
  auto n26 = gate_nand(n25, a[1]);
  auto n30 = gate_not(n28);
  auto n29 = gate_not(a[1]);
  auto n32 = gate_nand(n30, n29);
  auto n31 = gate_not(b[1]);
  auto n35 = gate_nand(n32, n31);
  auto n33 = gate_or(n15, a[1]);
  auto n34 = gate_nand(n33, a[2]);
  auto n37 = gate_and(n35, n34);
  auto n38 = gate_not(n37);
  auto n53 = gate_not(b[3]);
  auto n43 = gate_nand(n31, a[1]);
  auto n46 = gate_nand(n45, b[2]);
  auto n48 = gate_not(b[2]);
  auto n49 = gate_nand(n48, a[2]);
  auto n60 = gate_not(n59);
  auto n64 = gate_nor(n15, a[1]);
  auto n73 = gate_nand(n72, b[0]);
  auto n74 = gate_and(n73, n31);
  auto n2 = gate_and(n48, n53);
  auto n66 = gate_not(n2);
  auto n5 = gate_or(n37, b[3]);
  auto n7 = gate_or(n23, n24);
  auto n62 = gate_not(n25);
  y[2] = gate_and(n14, n2);
  auto n16 = gate_nor(n31, a[1]);
  auto n42 = gate_nor(n24, n16);
  auto n17 = gate_not(y[2]);
  auto n20 = gate_nand(n66, n19);
  auto n21 = gate_or(n48, a[2]);
  auto n27 = gate_and(n20, n21);
  auto n22 = gate_nand(n2, n31);
  auto n36 = gate_nand(n5, n66);
  auto n39 = gate_nand(n38, n2);
  auto n44 = gate_not(n42);
  auto n47 = gate_nand(n44, n43);
  auto n50 = gate_nand(n47, n46);
  auto n51 = gate_nand(n50, n49);
  auto n61 = gate_nor(n7, n60);
  auto n63 = gate_and(n62, n45);
  auto n65 = gate_nor(n64, n63);
  auto n68 = gate_xnor(n2, n67);
  auto n69 = gate_and(n20, n68);
  y[3] = gate_and(n2, n74);
  auto n3 = gate_and(n2, n61);
  auto n6 = gate_nand(n7, n26);
  auto n10 = gate_and(n42, y[2]);
  auto n11 = gate_nand(n65, n69);
  auto n12 = gate_and(n22, a[3]);
  auto n40 = gate_nand(n36, n12);
  auto n70 = gate_nand(n40, n39);
  auto n54 = gate_nand(n12, n53);
  auto n71 = gate_nand(n70, n17);
  y[1] = gate_nand(n11, n71);
  auto n1 = gate_not(n12);
  auto n4 = gate_and(n6, n12);
  auto n8 = gate_nor(n3, n10);
  auto n41 = gate_nand(n27, n4);
  auto n58 = gate_nand(n41, n70);
  auto n52 = gate_nand(n1, b[3]);
  auto n55 = gate_nand(n52, n51);
  auto n56 = gate_and(n55, n54);
  auto n57 = gate_nor(n56, y[2]);
  auto n9 = gate_nand(n57, n58);
  y[0] = gate_nand(n9, n8);
}
template<> void $NameUint<4>::d_divsig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n4 = gate_nand(b[0], b[1]);
  auto n63 = gate_not(n4);
  auto n5 = gate_xnor(b[3], b[1]);
  auto n12 = gate_buf(b[3]);
  auto n14 = gate_nand(a[0], a[1]);
  auto n15 = gate_not(n14);
  auto n25 = gate_not(a[0]);
  auto n26 = gate_not(b[0]);
  auto n76 = gate_nand(n15, a[3]);
  auto n39 = gate_buf(n5);
  auto n114 = gate_not(n5);
  auto n40 = gate_xnor(b[3], b[2]);
  auto n42 = gate_not(a[1]);
  auto n43 = gate_not(a[0]);
  auto n56 = gate_not(a[1]);
  auto n67 = gate_not(a[2]);
  auto n45 = gate_not(a[3]);
  auto n55 = gate_nand(a[3], a[0]);
  auto n59 = gate_nand(n45, n67);
  auto n61 = gate_and(a[3], a[2]);
  auto n94 = gate_not(b[2]);
  auto n62 = gate_not(b[1]);
  auto n152 = gate_nand(n94, n62);
  auto n79 = gate_not(b[3]);
  auto n66 = gate_nand(n152, n79);
  auto n64 = gate_nand(n63, b[2]);
  auto n65 = gate_nand(n64, n12);
  auto n73 = gate_xnor(n79, a[3]);
  auto n137 = gate_not(n73);
  auto n159 = gate_not(n137);
  auto n105 = gate_not(b[0]);
  auto n129 = gate_nand(n105, n94);
  auto n95 = gate_nand(n129, b[1]);
  auto n130 = gate_not(n129);
  auto n131 = gate_and(n130, a[3]);
  auto n151 = gate_nand(n12, b[2]);
  auto n153 = gate_nand(n152, n151);
  auto n168 = gate_buf(n105);
  auto n3 = gate_buf(n94);
  auto n9 = gate_nand(n15, a[3]);
  auto n11 = gate_nand(n168, b[3]);
  auto n13 = gate_not(n114);
  auto n120 = gate_nand(n66, n65);
  auto n24 = gate_nand(n25, b[0]);
  auto n161 = gate_nand(n26, b[3]);
  auto n75 = gate_nand(n55, n56);
  auto n32 = gate_not(n137);
  auto n163 = gate_not(n40);
  auto n41 = gate_not(n163);
  auto n60 = gate_nand(n43, n42);
  auto n44 = gate_nor(n45, a[2]);
  auto n106 = gate_nand(n60, n61);
  auto n77 = gate_and(n9, b[0]);
  auto n80 = gate_nand(n75, n77);
  auto n121 = gate_nand(n168, n79);
  auto n86 = gate_nand(n80, n121);
  auto n87 = gate_nand(n86, n39);
  auto n88 = gate_nand(n87, n163);
  auto n98 = gate_xnor(n95, n3);
  auto n96 = gate_and(n98, n137);
  auto n99 = gate_not(n98);
  auto n100 = gate_nand(n99, n159);
  auto n109 = gate_and(n106, b[0]);
  auto n132 = gate_nand(n131, n13);
  auto n148 = gate_and(n132, n159);
  auto n144 = gate_not(n148);
  auto n169 = gate_and(n106, n59);
  auto n171 = gate_nand(n161, n24);
  auto n1 = gate_buf(n120);
  auto n10 = gate_and(n76, n75);
  auto n17 = gate_and(n76, n75);
  auto n23 = gate_and(n161, n24);
  auto n38 = gate_and(n161, n24);
  auto n122 = gate_nand(n9, n75);
  auto n92 = gate_nand(n17, n23);
  auto n28 = gate_not(n32);
  auto n71 = gate_nand(n171, n122);
  auto n125 = gate_xnor(n23, n137);
  auto n54 = gate_nand(n92, n163);
  auto n150 = gate_and(n71, n13);
  auto n68 = gate_not(n60);
  auto n162 = gate_and(n68, n44);
  auto n49 = gate_and(n106, n59);
  auto n50 = gate_nand(n68, n67);
  auto n93 = gate_nand(n10, n168);
  auto n97 = gate_nand(n93, n92);
  auto n103 = gate_nor(n97, n137);
  auto n101 = gate_nand(n96, n97);
  auto n102 = gate_nand(n101, n100);
  auto n124 = gate_not(n1);
  auto n123 = gate_nand(n122, n121);
  auto n154 = gate_nand(n150, n153);
  auto n172 = gate_and(n49, n50);
  auto n115 = gate_nand(n162, n120);
  auto n7 = gate_buf(n162);
  auto n18 = gate_and(n71, n13);
  auto n34 = gate_and(n38, n40);
  auto n104 = gate_nor(n102, n103);
  auto n52 = gate_nand(n17, n34);
  auto n108 = gate_and(n50, n59);
  auto n74 = gate_nand(n169, n50);
  auto n111 = gate_not(n115);
  auto n51 = gate_and(n115, n52);
  auto n53 = gate_nand(n54, n172);
  auto n57 = gate_xnor(n18, n137);
  auto n135 = gate_nand(n123, n124);
  auto n72 = gate_nand(n74, n163);
  auto n81 = gate_nand(n114, n74);
  auto n84 = gate_nand(n81, n86);
  auto n83 = gate_nand(n172, n39);
  auto n85 = gate_nand(n84, n83);
  auto n89 = gate_nand(n88, n111);
  auto n110 = gate_nand(n109, n108);
  auto n113 = gate_and(n110, n121);
  auto n112 = gate_nand(n111, n39);
  auto n116 = gate_nand(n115, n114);
  auto n164 = gate_nand(n7, n11);
  auto n165 = gate_nor(n164, n163);
  auto n166 = gate_nand(n165, n13);
  auto n6 = gate_nand(n85, n41);
  auto n19 = gate_and(n135, n32);
  auto n21 = gate_and(n116, n41);
  auto n22 = gate_and(n89, n159);
  auto n29 = gate_nand(n6, n89);
  auto n30 = gate_nand(n22, n6);
  auto n36 = gate_nand(n72, n150);
  auto n90 = gate_nand(n85, n41);
  auto n46 = gate_not(n135);
  auto n47 = gate_nand(n112, n113);
  auto n69 = gate_nand(n53, n51);
  auto n126 = gate_nand(n46, n125);
  auto n138 = gate_nand(n46, n137);
  auto n170 = gate_and(n21, n135);
  auto n31 = gate_nand(n29, n28);
  auto n133 = gate_nand(n90, n89);
  auto n33 = gate_nand(n31, n30);
  auto n37 = gate_not(n69);
  auto n134 = gate_nand(n47, n21);
  auto n91 = gate_not(n133);
  auto n117 = gate_nand(n133, n104);
  auto n118 = gate_and(n117, n134);
  auto n157 = gate_buf(n134);
  auto n136 = gate_not(n134);
  auto n139 = gate_nand(n136, n19);
  auto n140 = gate_and(n139, n138);
  auto n58 = gate_and(n47, n170);
  auto n8 = gate_not(n136);
  auto n141 = gate_nand(n33, n8);
  auto n146 = gate_nand(n37, n36);
  auto n127 = gate_nand(n58, n57);
  auto n142 = gate_nand(n141, n140);
  auto n147 = gate_buf(n146);
  auto n149 = gate_nand(n147, n157);
  auto n158 = gate_and(n149, n148);
  auto n156 = gate_nand(n158, n154);
  auto n155 = gate_xnor(n8, n159);
  y[2] = gate_xnor(n156, n155);
  auto n160 = gate_nand(n158, n8);
  auto n167 = gate_nand(n160, n32);
  y[3] = gate_nand(n167, n166);
  auto n20 = gate_and(n127, n126);
  auto n35 = gate_xnor(n146, n32);
  auto n119 = gate_nand(n35, n91);
  auto n128 = gate_nand(n119, n118);
  auto n145 = gate_nand(n128, n20);
  auto n143 = gate_nand(n145, n148);
  y[1] = gate_xnor(n143, n142);
  y[0] = gate_xnor(n145, n144);
}
template<> void $NameUint<4>::d_eq
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n8 = gate_xnor(b[2], a[2]);
  auto n7 = gate_xnor(b[0], a[0]);
  auto n12 = gate_and(n8, n7);
  auto n10 = gate_xnor(a[3], b[3]);
  auto n9 = gate_xnor(b[1], a[1]);
  auto n11 = gate_and(n10, n9);
  auto _eq_x_1_n30 = gate_and(n12, n11);
  y[0] = gate_buf(_eq_x_1_n30);
}
template<> void $NameUint<4>::d_ge
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n15 = gate_not(a[0]);
  auto n16 = gate_nand(b[0], n15);
  auto n19 = gate_and(n16, a[1]);
  auto n17 = gate_nor(n16, a[1]);
  auto n18 = gate_nor(n17, b[1]);
  auto n22 = gate_nor(n19, n18);
  auto n20 = gate_not(a[2]);
  auto n21 = gate_and(n22, n20);
  auto n26 = gate_or(n21, b[2]);
  auto n27 = gate_or(n22, n20);
  auto n23 = gate_not(a[3]);
  auto n24 = gate_and(n27, n23);
  auto n25 = gate_and(n26, n24);
  auto n30 = gate_or(b[3], n25);
  auto n28 = gate_nand(n27, n26);
  auto n29 = gate_nand(n28, a[3]);
  auto _gte_x_1_n29 = gate_nand(n30, n29);
  y[0] = gate_buf(_gte_x_1_n29);
}
template<> void $NameUint<4>::d_gesig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n15 = gate_not(a[0]);
  auto n16 = gate_nand(b[0], n15);
  auto n19 = gate_and(n16, a[1]);
  auto n17 = gate_nor(n16, a[1]);
  auto n18 = gate_nor(n17, b[1]);
  auto n22 = gate_nor(n19, n18);
  auto n20 = gate_not(a[2]);
  auto n21 = gate_and(n22, n20);
  auto n26 = gate_or(n21, b[2]);
  auto n27 = gate_or(n22, n20);
  auto n23 = gate_not(b[3]);
  auto n24 = gate_and(n27, n23);
  auto n25 = gate_and(n26, n24);
  auto n30 = gate_or(a[3], n25);
  auto n28 = gate_nand(n27, n26);
  auto n29 = gate_nand(n28, b[3]);
  auto _gte_x_1_n29 = gate_nand(n30, n29);
  y[0] = gate_buf(_gte_x_1_n29);
}
template<> void $NameUint<4>::d_gt
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n17 = gate_not(b[0]);
  auto n19 = gate_and(a[0], n17);
  auto n18 = gate_nor(n19, a[1]);
  auto n21 = gate_nor(n18, b[1]);
  auto n20 = gate_and(n19, a[1]);
  auto n22 = gate_or(n21, n20);
  auto n25 = gate_nand(n22, a[2]);
  auto n23 = gate_nor(n22, a[2]);
  auto n28 = gate_or(n23, b[2]);
  auto n24 = gate_nand(n25, n28);
  auto n31 = gate_nand(n24, a[3]);
  auto n26 = gate_not(a[3]);
  auto n27 = gate_and(n26, n25);
  auto n29 = gate_and(n28, n27);
  auto n30 = gate_or(b[3], n29);
  auto _gt_x_1_n29 = gate_nand(n31, n30);
  y[0] = gate_buf(_gt_x_1_n29);
}
template<> void $NameUint<4>::d_gtsig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n17 = gate_not(b[0]);
  auto n19 = gate_and(a[0], n17);
  auto n18 = gate_nor(n19, a[1]);
  auto n21 = gate_nor(n18, b[1]);
  auto n20 = gate_and(n19, a[1]);
  auto n22 = gate_or(n21, n20);
  auto n25 = gate_nand(n22, a[2]);
  auto n23 = gate_nor(n22, a[2]);
  auto n28 = gate_or(n23, b[2]);
  auto n24 = gate_nand(n25, n28);
  auto n31 = gate_nand(n24, b[3]);
  auto n26 = gate_not(b[3]);
  auto n27 = gate_and(n26, n25);
  auto n29 = gate_and(n28, n27);
  auto n30 = gate_or(a[3], n29);
  auto _gt_x_1_n29 = gate_nand(n31, n30);
  y[0] = gate_buf(_gt_x_1_n29);
}
template<> void $NameUint<4>::d_inc
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  y[0] = gate_not(a[0]);
  y[1] = gate_xnor(a[1], y[0]);
  auto n4 = gate_and(a[0], a[1]);
  auto n3 = gate_nand(n4, a[2]);
  y[3] = gate_xnor(a[3], n3);
  y[2] = gate_xor(n4, a[2]);
}
template<> void $NameUint<4>::d_ineq
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n9 = gate_xnor(b[0], a[0]);
  auto n8 = gate_xnor(b[1], a[1]);
  auto n13 = gate_and(n9, n8);
  auto n11 = gate_xnor(b[2], a[2]);
  auto n10 = gate_xnor(b[3], a[3]);
  auto n12 = gate_and(n11, n10);
  y[0] = gate_nand(n13, n12);
}
template<> void $NameUint<4>::d_intmux
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b, const vector<Bit> & c) noexcept
{
  auto n4 = gate_or(a[1], a[0]);
  auto n5 = gate_or(a[2], n4);
  auto n6 = gate_nor(a[3], n5);
  y[0] = gate_mux(b[0], c[0], n6);
  y[1] = gate_mux(b[1], c[1], n6);
  y[2] = gate_mux(b[2], c[2], n6);
  y[3] = gate_mux(b[3], c[3], n6);
}
template<> void $NameUint<4>::d_le
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n18 = gate_not(b[0]);
  auto n19 = gate_nand(a[0], n18);
  auto n22 = gate_and(n19, b[1]);
  auto n20 = gate_nor(n19, b[1]);
  auto n21 = gate_nor(n20, a[1]);
  auto n25 = gate_nor(n22, n21);
  auto n23 = gate_not(b[2]);
  auto n24 = gate_and(n25, n23);
  auto n29 = gate_or(n24, a[2]);
  auto n30 = gate_or(n25, n23);
  auto n26 = gate_not(b[3]);
  auto n27 = gate_and(n30, n26);
  auto n28 = gate_and(n29, n27);
  auto n33 = gate_or(a[3], n28);
  auto n31 = gate_nand(n30, n29);
  auto n32 = gate_nand(n31, b[3]);
  y[0] = gate_nand(n33, n32);
}
template<> void $NameUint<4>::d_lesig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n18 = gate_not(b[0]);
  auto n19 = gate_nand(a[0], n18);
  auto n22 = gate_and(n19, b[1]);
  auto n20 = gate_nor(n19, b[1]);
  auto n21 = gate_nor(n20, a[1]);
  auto n25 = gate_nor(n22, n21);
  auto n23 = gate_not(b[2]);
  auto n24 = gate_and(n25, n23);
  auto n29 = gate_or(n24, a[2]);
  auto n30 = gate_or(n25, n23);
  auto n26 = gate_not(a[3]);
  auto n27 = gate_and(n30, n26);
  auto n28 = gate_and(n29, n27);
  auto n33 = gate_or(b[3], n28);
  auto n31 = gate_nand(n30, n29);
  auto n32 = gate_nand(n31, a[3]);
  y[0] = gate_nand(n33, n32);
}
template<> void $NameUint<4>::d_logand
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n8 = gate_nor(a[1], a[0]);
  auto n7 = gate_nor(a[3], a[2]);
  auto n12 = gate_nand(n8, n7);
  auto n10 = gate_nor(b[1], b[0]);
  auto n9 = gate_nor(b[3], b[2]);
  auto n11 = gate_nand(n10, n9);
  y[0] = gate_and(n12, n11);
}
template<> void $NameUint<4>::d_lognot
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_or(a[1], a[0]);
  auto n5 = gate_or(a[2], n4);
  y[0] = gate_nor(a[3], n5);
}
template<> void $NameUint<4>::d_logor
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n7 = gate_or(a[1], a[0]);
  auto n8 = gate_or(a[2], n7);
  auto n12 = gate_nor(a[3], n8);
  auto n9 = gate_or(b[1], b[0]);
  auto n10 = gate_or(b[2], n9);
  auto n11 = gate_nor(b[3], n10);
  y[0] = gate_nand(n12, n11);
}
template<> void $NameUint<4>::d_lt
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n16 = gate_not(a[0]);
  auto n18 = gate_and(b[0], n16);
  auto n17 = gate_nor(n18, b[1]);
  auto n20 = gate_nor(n17, a[1]);
  auto n19 = gate_and(n18, b[1]);
  auto n21 = gate_or(n20, n19);
  auto n24 = gate_nand(n21, b[2]);
  auto n22 = gate_nor(n21, b[2]);
  auto n27 = gate_or(n22, a[2]);
  auto n23 = gate_nand(n24, n27);
  auto n30 = gate_nand(n23, b[3]);
  auto n25 = gate_not(b[3]);
  auto n26 = gate_and(n25, n24);
  auto n28 = gate_and(n27, n26);
  auto n29 = gate_or(a[3], n28);
  y[0] = gate_nand(n30, n29);
}
template<> void $NameUint<4>::d_ltsig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n16 = gate_not(a[0]);
  auto n18 = gate_and(b[0], n16);
  auto n17 = gate_nor(n18, b[1]);
  auto n20 = gate_nor(n17, a[1]);
  auto n19 = gate_and(n18, b[1]);
  auto n21 = gate_or(n20, n19);
  auto n24 = gate_nand(n21, b[2]);
  auto n22 = gate_nor(n21, b[2]);
  auto n27 = gate_or(n22, a[2]);
  auto n23 = gate_nand(n24, n27);
  auto n30 = gate_nand(n23, a[3]);
  auto n25 = gate_not(a[3]);
  auto n26 = gate_and(n25, n24);
  auto n28 = gate_and(n27, n26);
  auto n29 = gate_or(b[3], n28);
  y[0] = gate_nand(n30, n29);
}
template<> void $NameUint<4>::d_mod
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n19 = gate_and(b[0], a[3]);
  auto n31 = gate_not(b[1]);
  auto n33 = gate_not(b[3]);
  auto n34 = gate_not(b[2]);
  auto n41 = gate_not(b[3]);
  auto n46 = gate_not(a[1]);
  auto n71 = gate_not(b[1]);
  auto n72 = gate_nand(n19, n71);
  auto n75 = gate_not(a[2]);
  auto n76 = gate_not(b[2]);
  auto n102 = gate_not(b[2]);
  auto n89 = gate_buf(a[3]);
  auto n93 = gate_not(b[3]);
  auto n86 = gate_not(a[3]);
  auto n91 = gate_nand(n86, b[1]);
  auto n98 = gate_not(b[2]);
  auto n97 = gate_not(a[0]);
  auto n125 = gate_nand(n97, b[0]);
  auto n128 = gate_not(n125);
  auto n107 = gate_nand(n128, b[1]);
  auto n108 = gate_not(n107);
  auto n110 = gate_not(a[2]);
  auto n126 = gate_xnor(n125, n31);
  auto n165 = gate_buf(n93);
  auto n169 = gate_nand(b[1], b[0]);
  auto n14 = gate_buf(n102);
  auto n25 = gate_nand(n125, n31);
  auto n144 = gate_nand(n34, n33);
  auto n40 = gate_nand(n41, b[0]);
  auto n42 = gate_not(n98);
  auto n68 = gate_nand(n46, b[0]);
  auto n51 = gate_and(n93, b[0]);
  auto n141 = gate_xnor(n89, n102);
  auto n66 = gate_nand(n98, n93);
  auto n92 = gate_nand(n75, b[0]);
  auto n74 = gate_and(n76, b[1]);
  auto n123 = gate_not(n68);
  auto n111 = gate_nand(n68, n31);
  auto n136 = gate_nand(n107, n14);
  auto n112 = gate_nand(n111, n110);
  auto n159 = gate_or(n169, a[1]);
  auto n1 = gate_and(n92, n91);
  auto n10 = gate_not(n66);
  auto n11 = gate_not(n14);
  auto n18 = gate_nand(n1, n10);
  auto n21 = gate_and(n10, n123);
  auto n88 = gate_xnor(n31, n68);
  auto n32 = gate_not(n144);
  auto n90 = gate_nand(n32, n71);
  auto n39 = gate_nor(n42, n40);
  auto n94 = gate_not(n88);
  auto n73 = gate_nand(n74, n92);
  auto n95 = gate_and(n159, a[2]);
  auto n96 = gate_nand(n95, n18);
  auto n119 = gate_nand(n96, n111);
  auto n151 = gate_nand(n108, n11);
  auto n142 = gate_and(n159, n112);
  auto n120 = gate_buf(n119);
  auto n8 = gate_nand(n10, n1);
  auto n60 = gate_nand(n90, n89);
  auto n12 = gate_and(n73, n72);
  auto n30 = gate_nor(n60, n66);
  auto n37 = gate_not(n142);
  auto n87 = gate_nand(n39, n91);
  auto n52 = gate_nand(n12, n141);
  auto n143 = gate_and(n12, n141);
  auto n147 = gate_and(n143, n142);
  auto n163 = gate_and(n8, n21);
  auto n170 = gate_and(n52, n165);
  auto n9 = gate_not(n60);
  auto n20 = gate_nand(n30, n18);
  auto n99 = gate_not(n20);
  auto n23 = gate_and(n87, a[2]);
  auto n104 = gate_nand(n94, n99);
  auto n103 = gate_nand(n23, n88);
  auto n114 = gate_nand(n52, n165);
  auto n64 = gate_and(n52, n51);
  auto n57 = gate_not(n23);
  auto n58 = gate_nand(n170, n94);
  auto n69 = gate_nand(n103, n136);
  auto n118 = gate_buf(n99);
  auto n115 = gate_buf(n114);
  auto n121 = gate_not(n115);
  auto n122 = gate_not(n118);
  auto n145 = gate_nand(n121, n120);
  auto n146 = gate_nand(n145, n144);
  auto n158 = gate_or(n57, n42);
  auto n160 = gate_not(n58);
  auto n85 = gate_nor(n160, n158);
  auto n63 = gate_nand(n9, n163);
  auto n166 = gate_and(n9, n8);
  auto n167 = gate_and(n9, n8);
  auto n172 = gate_buf(n121);
  auto n27 = gate_and(n20, a[1]);
  auto n22 = gate_and(n167, n37);
  auto n26 = gate_nand(n64, n119);
  auto n105 = gate_nand(n114, n23);
  auto n36 = gate_nand(n145, n122);
  auto n117 = gate_and(n58, n23);
  auto n137 = gate_and(n63, n25);
  auto n70 = gate_nand(n166, b[3]);
  auto n100 = gate_nor(n85, n118);
  auto n106 = gate_not(n105);
  auto n149 = gate_mux(n167, n147, n146);
  auto n161 = gate_and(n22, n172);
  auto n162 = gate_nand(n22, n172);
  auto n164 = gate_nand(n26, n27);
  auto n168 = gate_and(n105, n103);
  auto n124 = gate_nand(n27, n26);
  auto n28 = gate_buf(n168);
  auto n132 = gate_nand(n168, n104);
  auto n35 = gate_nand(n36, n123);
  auto n67 = gate_nand(n124, n137);
  auto n45 = gate_xnor(n132, n11);
  auto n49 = gate_and(n162, n117);
  auto n53 = gate_buf(n132);
  auto n61 = gate_nor(n106, n69);
  auto n62 = gate_nand(n70, b[3]);
  auto n101 = gate_not(n67);
  auto n153 = gate_not(n70);
  auto n77 = gate_nand(n161, b[0]);
  auto n84 = gate_nand(n101, n100);
  auto n133 = gate_nand(n53, n14);
  auto n152 = gate_nand(n28, n136);
  auto n138 = gate_nor(n137, n153);
  auto n139 = gate_nand(n152, n138);
  auto n154 = gate_nand(n152, n151);
  auto n155 = gate_nand(n154, n153);
  auto n7 = gate_nand(n35, n164);
  auto n38 = gate_nand(n61, n104);
  auto n43 = gate_buf(n67);
  auto n44 = gate_nand(n43, n107);
  auto n109 = gate_and(n62, n151);
  auto n65 = gate_and(n7, n162);
  auto n134 = gate_nor(n43, n70);
  auto n80 = gate_not(n84);
  auto n140 = gate_nand(n134, n133);
  auto n150 = gate_nand(n140, n139);
  auto n156 = gate_nand(n150, n149);
  y[3] = gate_nand(n156, n155);
  auto n171 = gate_xnor(n7, n126);
  auto n24 = gate_and(n38, b[0]);
  auto n83 = gate_and(n38, n109);
  auto n48 = gate_xnor(n45, n44);
  auto n78 = gate_nand(n24, n109);
  auto n79 = gate_nand(n80, n162);
  auto n55 = gate_nand(n83, n84);
  auto n81 = gate_nand(n77, n78);
  auto n127 = gate_nand(n81, n79);
  auto n131 = gate_nand(n127, a[0]);
  auto n3 = gate_buf(n55);
  auto n4 = gate_nand(n65, n3);
  auto n129 = gate_nand(n55, n162);
  auto n47 = gate_nand(n48, n129);
  auto n50 = gate_nand(n3, n49);
  auto n130 = gate_nand(n129, n128);
  y[0] = gate_nand(n131, n130);
  auto n5 = gate_nand(n171, n129);
  y[1] = gate_nand(n5, n4);
  y[2] = gate_nand(n47, n50);
}
template<> void $NameUint<4>::d_modsig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n10 = gate_nor(a[0], a[2]);
  auto n7 = gate_not(a[3]);
  auto n8 = gate_not(a[2]);
  auto n9 = gate_not(a[1]);
  auto n12 = gate_not(a[1]);
  auto n13 = gate_nor(b[0], b[3]);
  auto n158 = gate_not(n13);
  auto n17 = gate_nand(a[3], a[0]);
  auto n18 = gate_nand(a[3], a[0]);
  auto n24 = gate_nor(a[1], a[0]);
  auto n61 = gate_nand(a[2], a[3]);
  auto n37 = gate_not(b[0]);
  auto n48 = gate_not(a[2]);
  auto n53 = gate_not(a[3]);
  auto n57 = gate_nor(n18, n12);
  auto n58 = gate_nand(a[0], b[0]);
  auto n60 = gate_not(a[1]);
  auto n76 = gate_nand(a[3], a[0]);
  auto n99 = gate_not(a[1]);
  auto n114 = gate_nand(n76, n60);
  auto n183 = gate_not(b[0]);
  auto n77 = gate_not(a[0]);
  auto n78 = gate_xnor(b[3], b[1]);
  auto n90 = gate_not(n78);
  auto n82 = gate_not(b[3]);
  auto n83 = gate_xnor(n82, b[2]);
  auto n109 = gate_not(n83);
  auto n91 = gate_nand(n90, n109);
  auto n92 = gate_and(n114, b[0]);
  auto n96 = gate_xnor(a[0], a[3]);
  auto n95 = gate_xnor(n96, n183);
  auto n100 = gate_and(n99, a[3]);
  auto n101 = gate_nor(b[0], b[2]);
  auto n102 = gate_and(n101, b[1]);
  auto n105 = gate_nor(b[3], b[1]);
  auto n104 = gate_not(b[2]);
  auto n152 = gate_nand(n105, n104);
  auto n106 = gate_and(b[2], b[3]);
  auto n149 = gate_nand(n106, b[1]);
  auto n107 = gate_nand(n152, n149);
  auto n123 = gate_nand(n107, n158);
  auto n159 = gate_not(n158);
  auto n171 = gate_not(a[0]);
  auto n172 = gate_nand(n171, b[0]);
  auto n184 = gate_nand(n183, a[0]);
  auto n185 = gate_nand(n184, a[3]);
  auto n194 = gate_xnor(n82, b[2]);
  auto n148 = gate_nand(n7, n8);
  auto n153 = gate_nand(n10, n9);
  auto n14 = gate_not(n78);
  auto n15 = gate_not(n109);
  auto n113 = gate_nand(n37, b[3]);
  auto n19 = gate_and(n76, n12);
  auto n21 = gate_and(n58, n158);
  auto n27 = gate_nor(n17, n60);
  auto n160 = gate_not(n14);
  auto n150 = gate_or(n24, n61);
  auto n41 = gate_not(n95);
  auto n43 = gate_not(n113);
  auto n116 = gate_nor(n43, n57);
  auto n47 = gate_and(n77, n48);
  auto n75 = gate_not(n27);
  auto n84 = gate_nand(n21, n14);
  auto n56 = gate_nand(n58, n158);
  auto n80 = gate_not(n21);
  auto n179 = gate_nand(n80, n160);
  auto n145 = gate_not(n194);
  auto n93 = gate_nand(n92, n75);
  auto n110 = gate_and(n93, n158);
  auto n103 = gate_nand(n102, n113);
  auto n111 = gate_not(n110);
  auto n115 = gate_nand(n19, b[0]);
  auto n117 = gate_nand(n116, n115);
  auto n151 = gate_and(n149, n148);
  auto n155 = gate_and(n150, n151);
  auto n154 = gate_and(n153, n152);
  auto n156 = gate_nand(n155, n154);
  auto n161 = gate_xnor(n160, n159);
  auto n180 = gate_nor(n179, n15);
  auto n3 = gate_and(n100, n47);
  auto n6 = gate_nand(n153, n148);
  auto n121 = gate_xnor(n83, n3);
  auto n22 = gate_nand(n80, n160);
  auto n26 = gate_nand(n75, n114);
  auto n33 = gate_nand(n75, n114);
  auto n136 = gate_not(n33);
  auto n36 = gate_xnor(n56, n90);
  auto n178 = gate_and(n84, n136);
  auto n71 = gate_nor(n26, b[0]);
  auto n73 = gate_and(n26, b[0]);
  auto n79 = gate_nor(n33, b[0]);
  auto n81 = gate_nand(n79, n84);
  auto n87 = gate_and(n81, n179);
  auto n122 = gate_nand(n3, n103);
  auto n108 = gate_not(n122);
  auto n131 = gate_and(n108, n123);
  auto n112 = gate_not(n121);
  auto n127 = gate_and(n112, n111);
  auto n124 = gate_nor(n122, n194);
  auto n125 = gate_nand(n124, n123);
  auto n130 = gate_xnor(n26, a[3]);
  auto n132 = gate_not(n131);
  auto n177 = gate_nand(n22, n15);
  auto n181 = gate_nor(n178, n177);
  auto n182 = gate_nor(n181, n180);
  auto n62 = gate_not(n6);
  auto n25 = gate_nand(n84, n136);
  auto n35 = gate_nand(n62, n150);
  auto n169 = gate_xnor(n36, n136);
  auto n67 = gate_nand(n62, n150);
  auto n118 = gate_nand(n62, n37);
  auto n49 = gate_not(n125);
  auto n51 = gate_nor(n49, n156);
  auto n120 = gate_nand(n67, n14);
  auto n94 = gate_nor(n35, n91);
  auto n88 = gate_nand(n35, n15);
  auto n162 = gate_nor(n35, b[0]);
  auto n70 = gate_nor(n71, a[0]);
  auto n166 = gate_nand(n94, n110);
  auto n97 = gate_and(n166, n96);
  auto n119 = gate_nand(n118, n117);
  auto n133 = gate_and(n166, n132);
  auto n188 = gate_nand(n25, n22);
  auto n146 = gate_nand(n188, n145);
  auto n170 = gate_not(n169);
  auto n4 = gate_and(n88, n95);
  auto n5 = gate_nand(n162, n161);
  auto n59 = gate_xnor(n169, a[3]);
  auto n39 = gate_buf(n120);
  auto n54 = gate_or(n166, n41);
  auto n74 = gate_and(n120, n119);
  auto n85 = gate_nand(n39, n145);
  auto n86 = gate_nand(n85, n178);
  auto n126 = gate_nand(n74, n121);
  auto n29 = gate_nand(n86, n87);
  auto n31 = gate_nand(n74, n121);
  auto n42 = gate_nand(n29, n88);
  auto n89 = gate_nand(n86, n87);
  auto n50 = gate_nand(n51, n31);
  auto n157 = gate_nand(n126, n125);
  auto n139 = gate_nand(n42, n97);
  auto n55 = gate_nand(n89, n4);
  auto n147 = gate_nand(n42, n166);
  auto n65 = gate_nand(n147, n146);
  auto n168 = gate_nand(n157, b[0]);
  auto n72 = gate_nand(n157, n73);
  auto n134 = gate_xnor(n168, n130);
  auto n1 = gate_buf(n42);
  auto n2 = gate_and(n50, n5);
  auto n16 = gate_nand(n42, n133);
  auto n135 = gate_not(n16);
  auto n28 = gate_buf(n168);
  auto n30 = gate_not(n147);
  auto n44 = gate_nand(n157, n127);
  auto n46 = gate_not(n157);
  auto n66 = gate_xnor(n2, a[3]);
  auto n140 = gate_nand(n55, n54);
  auto n137 = gate_xnor(n168, n59);
  auto n163 = gate_xnor(n66, n65);
  auto n68 = gate_nand(n46, n136);
  auto n69 = gate_and(n72, n70);
  auto n138 = gate_nand(n134, n135);
  auto n173 = gate_nand(n28, n170);
  auto n174 = gate_nand(n173, n172);
  auto n186 = gate_nor(n2, n182);
  auto n187 = gate_nor(n186, n185);
  auto n193 = gate_not(n140);
  auto n40 = gate_nand(n137, n16);
  auto n45 = gate_nand(n46, n131);
  auto n52 = gate_nor(n140, n53);
  auto n165 = gate_nand(n69, n68);
  auto n176 = gate_nand(n165, n1);
  auto n128 = gate_and(n193, n139);
  auto n32 = gate_nand(n45, n44);
  auto n34 = gate_and(n138, n40);
  auto n143 = gate_nand(n40, n138);
  auto n189 = gate_nand(n45, n44);
  auto n142 = gate_and(n52, n139);
  auto n64 = gate_and(n176, n187);
  auto n141 = gate_nand(n189, b[0]);
  auto n129 = gate_nand(n128, n141);
  y[0] = gate_xnor(n129, a[3]);
  auto n144 = gate_and(n142, n141);
  auto n164 = gate_nand(n143, n144);
  y[2] = gate_xnor(n164, n163);
  auto n167 = gate_not(n32);
  auto n190 = gate_nand(n32, n188);
  auto n191 = gate_and(n190, a[3]);
  auto n23 = gate_and(n142, n141);
  auto n175 = gate_nand(n167, n30);
  auto n63 = gate_nand(n175, n174);
  y[1] = gate_xnor(n34, n23);
  auto n38 = gate_nand(n64, n63);
  y[3] = gate_xnor(n38, n191);
}
template<> void $NameUint<4>::d_mul
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[0] = gate_and(a[0], b[0]);
  auto n2 = gate_and(b[1], a[0]);
  auto n1 = gate_and(a[1], b[0]);
  y[1] = gate_xor(n2, n1);
  auto n11 = gate_and(n2, n1);
  auto n9 = gate_and(a[2], b[0]);
  auto n5 = gate_xnor(n11, n9);
  auto n4 = gate_nand(b[2], a[0]);
  auto n3 = gate_nand(a[1], b[1]);
  auto n8 = gate_xor(n4, n3);
  y[2] = gate_xnor(n5, n8);
  auto n7 = gate_and(a[3], b[0]);
  auto n6 = gate_nand(b[3], a[0]);
  auto n15 = gate_xnor(n7, n6);
  auto n13 = gate_or(n9, n8);
  auto n10 = gate_and(n9, n8);
  auto n12 = gate_or(n11, n10);
  auto n14 = gate_nand(n13, n12);
  auto n20 = gate_xnor(n15, n14);
  auto n18 = gate_nand(a[1], b[2]);
  auto n16 = gate_nor(a[0], n18);
  auto n17 = gate_xnor(n16, a[2]);
  auto n19 = gate_mux(n18, n17, b[1]);
  y[3] = gate_xnor(n20, n19);
}
template<> void $NameUint<4>::d_redand
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_nand(a[0], a[1]);
  auto n3 = gate_nand(a[2], a[3]);
  y[0] = gate_nor(n4, n3);
}
template<> void $NameUint<4>::d_rednand
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n5 = gate_and(a[1], a[3]);
  auto n4 = gate_and(a[2], a[0]);
  y[0] = gate_nand(n5, n4);
}
template<> void $NameUint<4>::d_rednor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_or(a[1], a[0]);
  auto n5 = gate_or(a[2], n4);
  y[0] = gate_nor(a[3], n5);
}
template<> void $NameUint<4>::d_redor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_nor(a[1], a[0]);
  auto n3 = gate_nor(a[3], a[2]);
  y[0] = gate_nand(n4, n3);
}
template<> void $NameUint<4>::d_redxnor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_xnor(a[1], a[2]);
  auto n5 = gate_xnor(n4, a[0]);
  y[0] = gate_xnor(a[3], n5);
}
template<> void $NameUint<4>::d_redxor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  auto n4 = gate_xor(a[0], a[1]);
  auto n3 = gate_xnor(a[3], a[2]);
  y[0] = gate_xnor(n4, n3);
}
template<> void $NameUint<4>::d_sll
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n24 = gate_not(b[0]);
  auto n26 = gate_or(b[3], b[2]);
  auto n33 = gate_nor(b[1], n26);
  auto n25 = gate_and(n24, n33);
  auto _ash_1_n16 = gate_and(a[0], n25);
  auto n34 = gate_mux(a[1], a[0], b[0]);
  y[1] = gate_and(n33, n34);
  auto n27 = gate_not(n26);
  auto n35 = gate_and(b[1], n27);
  auto n28 = gate_nand(a[0], n35);
  auto n31 = gate_nor(b[0], n28);
  auto n29 = gate_mux(a[2], a[1], b[0]);
  auto n30 = gate_and(n33, n29);
  y[2] = gate_or(n31, n30);
  auto n32 = gate_mux(a[3], a[2], b[0]);
  auto n37 = gate_nand(n33, n32);
  auto n36 = gate_nand(n35, n34);
  y[3] = gate_nand(n37, n36);
  y[0] = gate_buf(_ash_1_n16);
}
template<> void $NameUint<4>::d_slr
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto n15 = gate_not(b[0]);
  auto n17 = gate_or(b[2], b[3]);
  auto n24 = gate_nor(b[1], n17);
  auto n16 = gate_and(n15, n24);
  y[3] = gate_and(a[3], n16);
  auto n25 = gate_mux(a[2], a[3], b[0]);
  y[2] = gate_and(n24, n25);
  auto n18 = gate_not(n17);
  auto n26 = gate_and(b[1], n18);
  auto n19 = gate_nand(a[3], n26);
  auto n22 = gate_nor(b[0], n19);
  auto n20 = gate_mux(a[1], a[2], b[0]);
  auto n21 = gate_and(n24, n20);
  y[1] = gate_or(n22, n21);
  auto n23 = gate_mux(a[0], a[1], b[0]);
  auto n28 = gate_nand(n24, n23);
  auto n27 = gate_nand(n26, n25);
  y[0] = gate_nand(n28, n27);
}
template<> void $NameUint<4>::d_srasig
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  auto one = gate_xnor(a[0], a[0]);
  y[3] = gate_buf(a[3]);
  auto n15 = gate_and(b[0], b[1]);
  auto n19 = gate_and(a[3], n15);
  auto n16 = gate_nand(b[1], a[2]);
  auto n17 = gate_nor(b[0], n16);
  auto n20 = gate_or(b[3], b[2]);
  auto n18 = gate_mux(n17, a[3], n20);
  auto n23 = gate_or(n19, n18);
  auto n28 = gate_nor(b[1], n20);
  auto n21 = gate_mux(a[0], a[1], b[0]);
  auto n22 = gate_and(n28, n21);
  y[0] = gate_or(n23, n22);
  auto n24 = gate_mux(a[1], a[2], b[0]);
  auto n27 = gate_nand(n28, n24);
  auto n26 = gate_mux(one, n28, a[3]);
  y[1] = gate_nand(n27, n26);
  auto n29 = gate_not(b[0]);
  auto n30 = gate_and(n29, n28);
  y[2] = gate_mux(a[3], a[2], n30);
}
template<> void $NameUint<4>::d_sub
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
  y[0] = gate_xor(a[0], b[0]);
  auto n16 = gate_xnor(a[1], b[1]);
  auto n13 = gate_not(a[0]);
  auto n15 = gate_nand(b[0], n13);
  y[1] = gate_xor(n16, n15);
  auto n20 = gate_xnor(a[2], b[2]);
  auto n14 = gate_not(b[1]);
  auto n18 = gate_nand(a[1], n14);
  auto n17 = gate_nand(n16, n15);
  auto n19 = gate_nand(n18, n17);
  y[2] = gate_xor(n20, n19);
  auto n23 = gate_nand(n20, n19);
  auto n21 = gate_not(b[2]);
  auto n22 = gate_nand(a[2], n21);
  auto n25 = gate_and(n23, n22);
  auto n24 = gate_xnor(b[3], a[3]);
  y[3] = gate_xnor(n25, n24);
}
template<> void $NameUint<4>::d_uminus
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
  y[0] = gate_buf(a[0]);
  y[1] = gate_xor(a[1], a[0]);
  auto n3 = gate_or(a[1], a[0]);
  y[2] = gate_xor(a[2], n3);
  auto n4 = gate_nor(a[2], n3);
  y[3] = gate_xnor(a[3], n4);
}
