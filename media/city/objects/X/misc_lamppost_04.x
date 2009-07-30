xof 0303txt 0032
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}

template EffectInstance {
 <e331f7e4-0559-4cc2-8e99-1cec1657928f>
 STRING EffectFilename;
 [...]
}

template EffectParamFloats {
 <3014b9a0-62f5-478c-9b86-e4ac9f4e418b>
 STRING ParamName;
 DWORD nFloats;
 array FLOAT Floats[nFloats];
}

template EffectParamString {
 <1dbc4c88-94c1-46ee-9076-2c28818c9481>
 STRING ParamName;
 STRING Value;
}

template EffectParamDWord {
 <e13963bc-ae51-4c5d-b00f-cfa3a9d97ce5>
 STRING ParamName;
 DWORD Value;
}


Material skyscrapers {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Skyscrp.tga";
 }
}

Material buildz1 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz1.tga";
 }
}

Material buildz3 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz3.tga";
 }
}

Material buildz4 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz4.tga";
 }
}

Material buildz5 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz5.tga";
 }
}

Material buildz6 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz6.tga";
 }
}

Material buildz2 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "buildz2.tga";
 }
}

Material roads {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "roads.tga";
 }
}

Material roads-2 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "roads2.tga";
 }
}

Material tree-01 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "trees-02.tga";
 }
}

Frame misc_lamppost_04 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,-1.000000,0.000000,0.000000,1.000000,-0.000000,0.000000,-0.004512,-12.658485,12.751022,1.000000;;
 }

 Frame {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.000000,0.000000,1.000000;;
  }

  Mesh  {
   111;
   -0.170857;0.147019;7.275969;,
   -0.175739;-0.142019;7.275969;,
   0.113299;-0.146901;7.275969;,
   0.113299;-0.146901;7.275969;,
   0.118181;0.142138;7.275969;,
   -0.170857;0.147019;7.275969;,
   0.118181;0.142138;7.275969;,
   0.113299;-0.146901;7.275969;,
   0.163586;-0.195303;0.000000;,
   0.163586;-0.195303;0.000000;,
   0.170073;0.188814;0.000000;,
   0.118181;0.142138;7.275969;,
   -0.170857;0.147019;7.275969;,
   0.118181;0.142138;7.275969;,
   0.170073;0.188814;0.000000;,
   0.170073;0.188814;0.000000;,
   -0.214044;0.195302;0.000000;,
   -0.170857;0.147019;7.275969;,
   -0.175739;-0.142019;7.275969;,
   -0.170857;0.147019;7.275969;,
   -0.214044;0.195302;0.000000;,
   -0.214044;0.195302;0.000000;,
   -0.220532;-0.188816;0.000000;,
   -0.175739;-0.142019;7.275969;,
   0.113299;-0.146901;7.275969;,
   -0.175739;-0.142019;7.275969;,
   -0.220532;-0.188816;0.000000;,
   -0.220532;-0.188816;0.000000;,
   0.163586;-0.195303;0.000000;,
   0.113299;-0.146901;7.275969;,
   -0.045808;-0.958652;7.299580;,
   0.117522;-1.075718;6.880230;,
   0.099870;1.430989;7.715662;,
   0.099870;1.430989;7.715662;,
   -0.030532;1.430989;8.034435;,
   -0.045808;-0.958652;7.299580;,
   -0.232221;-1.074046;6.880498;,
   -0.183912;1.430989;7.715341;,
   0.099870;1.430989;7.715662;,
   0.099870;1.430989;7.715662;,
   0.117522;-1.075718;6.880230;,
   -0.232221;-1.074046;6.880498;,
   -0.045808;-0.958652;7.299580;,
   -0.030532;1.430989;8.034435;,
   -0.183912;1.430989;7.715341;,
   -0.183912;1.430989;7.715341;,
   -0.232221;-1.074046;6.880498;,
   -0.045808;-0.958652;7.299580;,
   -0.045808;-0.958652;7.299580;,
   -0.232221;-1.074046;6.880498;,
   0.117522;-1.075718;6.880230;,
   -0.386045;2.860581;7.961908;,
   -0.245323;2.854714;8.339647;,
   -0.376821;4.621931;8.097751;,
   -0.204670;4.338091;8.435802;,
   -0.376821;4.621931;8.097751;,
   -0.245323;2.854714;8.339647;,
   -0.245323;2.854714;8.339647;,
   0.176494;2.853824;8.344447;,
   -0.204670;4.338091;8.435802;,
   0.135294;4.336909;8.442182;,
   -0.204670;4.338091;8.435802;,
   0.176494;2.853824;8.344447;,
   0.176494;2.853824;8.344447;,
   0.320960;2.859691;7.966708;,
   0.135294;4.336909;8.442182;,
   0.312875;4.620749;8.104129;,
   0.135294;4.336909;8.442182;,
   0.320960;2.859691;7.966708;,
   0.320960;2.859691;7.966708;,
   -0.386045;2.860581;7.961908;,
   0.312875;4.620749;8.104129;,
   -0.376821;4.621931;8.097751;,
   0.312875;4.620749;8.104129;,
   -0.386045;2.860581;7.961908;,
   0.135294;4.336909;8.442182;,
   0.312875;4.620749;8.104129;,
   -0.204670;4.338091;8.435802;,
   -0.376821;4.621931;8.097751;,
   -0.204670;4.338091;8.435802;,
   0.312875;4.620749;8.104129;,
   -0.245323;2.854714;8.339647;,
   -0.386045;2.860581;7.961908;,
   -0.248751;1.420342;7.679319;,
   -0.248751;1.420342;7.679319;,
   -0.155702;1.411058;8.051117;,
   -0.245323;2.854714;8.339647;,
   0.176494;2.853824;8.344447;,
   -0.245323;2.854714;8.339647;,
   -0.155702;1.411058;8.051117;,
   -0.155702;1.411058;8.051117;,
   0.082816;1.410619;8.056959;,
   0.176494;2.853824;8.344447;,
   0.320960;2.859691;7.966708;,
   0.176494;2.853824;8.344447;,
   0.082816;1.410619;8.056959;,
   0.082816;1.410619;8.056959;,
   0.178391;1.419903;7.685158;,
   0.320960;2.859691;7.966708;,
   -0.386045;2.860581;7.961908;,
   0.320960;2.859691;7.966708;,
   0.178391;1.419903;7.685158;,
   0.178391;1.419903;7.685158;,
   -0.248751;1.420342;7.679319;,
   -0.386045;2.860581;7.961908;,
   0.178391;1.419903;7.685158;,
   0.082816;1.410619;8.056959;,
   -0.155702;1.411058;8.051117;,
   -0.155702;1.411058;8.051117;,
   -0.248751;1.420342;7.679319;,
   0.178391;1.419903;7.685158;;
   37;
   3;0,1,2;,
   3;3,4,5;,
   3;6,7,8;,
   3;9,10,11;,
   3;12,13,14;,
   3;15,16,17;,
   3;18,19,20;,
   3;21,22,23;,
   3;24,25,26;,
   3;27,28,29;,
   3;30,31,32;,
   3;33,34,35;,
   3;36,37,38;,
   3;39,40,41;,
   3;42,43,44;,
   3;45,46,47;,
   3;48,49,50;,
   3;51,52,53;,
   3;54,55,56;,
   3;57,58,59;,
   3;60,61,62;,
   3;63,64,65;,
   3;66,67,68;,
   3;69,70,71;,
   3;72,73,74;,
   3;75,76,77;,
   3;78,79,80;,
   3;81,82,83;,
   3;84,85,86;,
   3;87,88,89;,
   3;90,91,92;,
   3;93,94,95;,
   3;96,97,98;,
   3;99,100,101;,
   3;102,103,104;,
   3;105,106,107;,
   3;108,109,110;;

   MeshNormals  {
    111;
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.999833;-0.016886;0.007023;,
    0.999833;-0.016886;0.007023;,
    0.999833;-0.016886;0.007022;,
    0.999833;-0.016886;0.007022;,
    0.999833;-0.016886;0.007022;,
    0.999833;-0.016886;0.007023;,
    0.016886;0.999836;0.006535;,
    0.016886;0.999836;0.006535;,
    0.016887;0.999836;0.006535;,
    0.016887;0.999836;0.006535;,
    0.016887;0.999836;0.006535;,
    0.016886;0.999836;0.006535;,
    -0.999839;0.016886;0.006047;,
    -0.999839;0.016887;0.006047;,
    -0.999839;0.016886;0.006047;,
    -0.999839;0.016886;0.006047;,
    -0.999839;0.016886;0.006047;,
    -0.999839;0.016886;0.006047;,
    -0.016886;-0.999836;0.006535;,
    -0.016886;-0.999836;0.006535;,
    -0.016887;-0.999836;0.006535;,
    -0.016887;-0.999836;0.006535;,
    -0.016887;-0.999836;0.006535;,
    -0.016886;-0.999836;0.006535;,
    0.912944;-0.123385;0.388984;,
    0.912535;-0.123519;0.389900;,
    0.918172;-0.121626;0.377051;,
    0.918172;-0.121626;0.377051;,
    0.918702;-0.121443;0.375817;,
    0.912944;-0.123385;0.388984;,
    0.000805;0.316183;-0.948698;,
    0.001073;0.316151;-0.948708;,
    0.001049;0.316154;-0.948707;,
    0.001049;0.316154;-0.948707;,
    0.000785;0.316186;-0.948697;,
    0.000805;0.316183;-0.948698;,
    -0.781514;-0.418501;0.462701;,
    -0.894053;-0.126439;0.429747;,
    -0.893948;-0.126470;0.429956;,
    -0.893948;-0.126470;0.429956;,
    -0.532156;-0.725469;0.436469;,
    -0.781514;-0.418501;0.462701;,
    -0.781514;-0.418501;0.462701;,
    -0.532156;-0.725469;0.436469;,
    -0.004400;-0.963607;0.267288;,
    -0.933497;-0.092986;0.346319;,
    -0.934771;-0.079488;0.346243;,
    -0.518980;0.514859;0.682334;,
    -0.583748;0.451869;0.674576;,
    -0.518980;0.514859;0.682334;,
    -0.934771;-0.079488;0.346243;,
    -0.011556;-0.130054;0.991440;,
    -0.012770;-0.130041;0.991426;,
    -0.017652;-0.065938;0.997668;,
    -0.018953;-0.066269;0.997622;,
    -0.017652;-0.065938;0.997668;,
    -0.012770;-0.130041;0.991426;,
    0.932665;-0.059701;0.355768;,
    0.932519;-0.071778;0.353915;,
    0.900445;-0.026569;0.434158;,
    0.895215;-0.030583;0.444583;,
    0.900445;-0.026569;0.434158;,
    0.932519;-0.071778;0.353915;,
    0.006896;0.133047;-0.991086;,
    0.007805;0.133214;-0.991057;,
    0.008750;0.077082;-0.996986;,
    0.009352;0.076844;-0.996999;,
    0.008750;0.077082;-0.996986;,
    0.007805;0.133214;-0.991057;,
    -0.009342;0.768222;0.640116;,
    -0.006565;0.766123;0.642660;,
    -0.583748;0.451869;0.674576;,
    -0.518980;0.514859;0.682334;,
    -0.583748;0.451869;0.674576;,
    -0.006565;0.766123;0.642660;,
    -0.934771;-0.079488;0.346243;,
    -0.933497;-0.092986;0.346319;,
    -0.671457;-0.722588;0.164354;,
    -0.671457;-0.722588;0.164354;,
    -0.628781;-0.765229;0.138057;,
    -0.934771;-0.079488;0.346243;,
    -0.012770;-0.130041;0.991426;,
    -0.011556;-0.130054;0.991440;,
    -0.022156;-0.194285;0.980695;,
    -0.022156;-0.194285;0.980695;,
    -0.024379;-0.193782;0.980742;,
    -0.012770;-0.130041;0.991426;,
    0.932519;-0.071778;0.353915;,
    0.932665;-0.059701;0.355768;,
    0.955083;-0.140717;0.260797;,
    0.955083;-0.140717;0.260797;,
    0.959475;-0.142542;0.243083;,
    0.932519;-0.071778;0.353915;,
    0.007805;0.133214;-0.991057;,
    0.006896;0.133047;-0.991086;,
    0.011745;0.193070;-0.981115;,
    0.011745;0.193070;-0.981115;,
    0.013610;0.193770;-0.980953;,
    0.007805;0.133214;-0.991057;,
    -0.000884;-0.999688;-0.024968;,
    -0.001223;-0.999680;-0.025276;,
    -0.628781;-0.765229;0.138057;,
    -0.628781;-0.765229;0.138057;,
    -0.671457;-0.722588;0.164354;,
    -0.000884;-0.999688;-0.024968;;
    37;
    3;0,1,2;,
    3;3,4,5;,
    3;6,7,8;,
    3;9,10,11;,
    3;12,13,14;,
    3;15,16,17;,
    3;18,19,20;,
    3;21,22,23;,
    3;24,25,26;,
    3;27,28,29;,
    3;30,31,32;,
    3;33,34,35;,
    3;36,37,38;,
    3;39,40,41;,
    3;42,43,44;,
    3;45,46,47;,
    3;48,49,50;,
    3;51,52,53;,
    3;54,55,56;,
    3;57,58,59;,
    3;60,61,62;,
    3;63,64,65;,
    3;66,67,68;,
    3;69,70,71;,
    3;72,73,74;,
    3;75,76,77;,
    3;78,79,80;,
    3;81,82,83;,
    3;84,85,86;,
    3;87,88,89;,
    3;90,91,92;,
    3;93,94,95;,
    3;96,97,98;,
    3;99,100,101;,
    3;102,103,104;,
    3;105,106,107;,
    3;108,109,110;;
   }

   MeshMaterialList  {
    1;
    37;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;
    { roads }
   }

   MeshTextureCoords  {
    111;
    0.999163;0.722927;,
    0.999165;0.705445;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.999163;0.722927;,
    0.999163;0.722927;,
    0.999165;0.705445;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.999163;0.722927;,
    0.999163;0.722927;,
    0.999165;0.705445;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.999163;0.722927;,
    0.999163;0.722927;,
    0.999165;0.705445;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.999163;0.722927;,
    0.999163;0.722927;,
    0.999165;0.705445;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.999163;0.722927;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.712346;0.722927;,
    0.712346;0.722927;,
    0.708144;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.712253;0.722927;,
    0.712347;0.705445;,
    0.712347;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.541139;0.722927;,
    0.708143;0.722927;,
    0.712253;0.705445;,
    0.712253;0.705445;,
    0.541139;0.705445;,
    0.541139;0.722927;,
    0.541139;0.722927;,
    0.541139;0.705445;,
    0.541139;0.705445;,
    0.897651;0.813367;,
    0.897650;0.781118;,
    0.790309;0.813367;,
    0.790309;0.781119;,
    0.790309;0.813367;,
    0.897650;0.781118;,
    0.897651;0.781119;,
    0.897650;0.813367;,
    0.790309;0.781118;,
    0.790309;0.813367;,
    0.790309;0.781118;,
    0.897650;0.813367;,
    0.897651;0.781119;,
    0.897650;0.813367;,
    0.790309;0.781118;,
    0.790309;0.813367;,
    0.790309;0.781118;,
    0.897650;0.813367;,
    0.806615;0.735603;,
    0.806615;0.746995;,
    0.833017;0.734375;,
    0.831095;0.748106;,
    0.833017;0.734375;,
    0.806615;0.746995;,
    0.805075;0.781990;,
    0.803229;0.812495;,
    0.847526;0.781119;,
    0.847526;0.813367;,
    0.847526;0.781119;,
    0.803229;0.812495;,
    0.897650;0.781118;,
    0.897651;0.813367;,
    0.790309;0.813367;,
    0.790309;0.813367;,
    0.790309;0.781119;,
    0.897650;0.781118;,
    0.897650;0.813367;,
    0.897651;0.781119;,
    0.790309;0.781118;,
    0.790309;0.781118;,
    0.790309;0.813367;,
    0.897650;0.813367;,
    0.897650;0.813367;,
    0.897651;0.781119;,
    0.790309;0.781118;,
    0.790309;0.781118;,
    0.790309;0.813367;,
    0.897650;0.813367;,
    0.806615;0.746995;,
    0.806615;0.735603;,
    0.833017;0.734375;,
    0.833017;0.734375;,
    0.831095;0.748106;,
    0.806615;0.746995;,
    0.803229;0.812495;,
    0.805075;0.781990;,
    0.847526;0.781119;,
    0.847526;0.781119;,
    0.847526;0.813367;,
    0.803229;0.812495;;
   }
  }
 }
}