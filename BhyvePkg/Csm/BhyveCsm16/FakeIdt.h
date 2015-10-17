// Fake Idt handlers. Restrict which set of Idt handlers are registered
// otherwise build output becomes oversaturated.

#define FAKE_IDTS
#define XBLOCK 1

#if XBLOCK == 1
VOID
Fidt_0(VOID)
{
  DEBUG(("Idt 0\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_1(VOID)
{
  DEBUG(("Idt 1\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_2(VOID)
{
  DEBUG(("Idt 2\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_3(VOID)
{
  DEBUG(("Idt 3\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_4(VOID)
{
  DEBUG(("Idt 4\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_5(VOID)
{
  DEBUG(("Idt 5\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_6(VOID)
{
  DEBUG(("Idt 6\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_7(VOID)
{
  DEBUG(("Idt 7\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_8(VOID)
{
  DEBUG(("Idt 8\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_9(VOID)
{
  DEBUG(("Idt 9\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_10(VOID)
{
  DEBUG(("Idt 10\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_11(VOID)
{
  DEBUG(("Idt 11\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_12(VOID)
{
  DEBUG(("Idt 12\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_13(VOID)
{
  DEBUG(("Idt 13\n"));
  for(;;);
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_14(VOID)
{
  DEBUG(("Idt 14\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_15(VOID)
{
  DEBUG(("Idt 15\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_16(VOID)
{
  DEBUG(("Idt 16\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_17(VOID)
{
  DEBUG(("Idt 17\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_18(VOID)
{
  DEBUG(("Idt 18\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_19(VOID)
{
  DEBUG(("Idt 19\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_20(VOID)
{
  DEBUG(("Idt 20\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_21(VOID)
{
  DEBUG(("Idt 21\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_22(VOID)
{
  DEBUG(("Idt 22\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_23(VOID)
{
  DEBUG(("Idt 23\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_24(VOID)
{
  DEBUG(("Idt 24\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_25(VOID)
{
  DEBUG(("Idt 25\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_26(VOID)
{
  DEBUG(("Idt 26\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_27(VOID)
{
  DEBUG(("Idt 27\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_28(VOID)
{
  DEBUG(("Idt 28\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_29(VOID)
{
  DEBUG(("Idt 29\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_30(VOID)
{
  DEBUG(("Idt 30\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_31(VOID)
{
  DEBUG(("Idt 31\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_32(VOID)
{
  DEBUG(("Idt 32\n"));
__asm__ __volatile__ ("outb %b0,%w1" : : "a" (0), "d" ((UINT16)0x488));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_33(VOID)
{
  DEBUG(("Idt 33\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_34(VOID)
{
  DEBUG(("Idt 34\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_35(VOID)
{
  DEBUG(("Idt 35\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_36(VOID)
{
  DEBUG(("Idt 36\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_37(VOID)
{
  DEBUG(("Idt 37\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_38(VOID)
{
  DEBUG(("Idt 38\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_39(VOID)
{
  DEBUG(("Idt 39\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_40(VOID)
{
  DEBUG(("Idt 40\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_41(VOID)
{
  DEBUG(("Idt 41\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_42(VOID)
{
  DEBUG(("Idt 42\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_43(VOID)
{
  DEBUG(("Idt 43\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_44(VOID)
{
  DEBUG(("Idt 44\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_45(VOID)
{
  DEBUG(("Idt 45\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_46(VOID)
{
  DEBUG(("Idt 46\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_47(VOID)
{
  DEBUG(("Idt 47\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_48(VOID)
{
  DEBUG(("Idt 48\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_49(VOID)
{
  DEBUG(("Idt 49\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_50(VOID)
{
  DEBUG(("Idt 50\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_51(VOID)
{
  DEBUG(("Idt 51\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_52(VOID)
{
  DEBUG(("Idt 52\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_53(VOID)
{
  DEBUG(("Idt 53\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_54(VOID)
{
  DEBUG(("Idt 54\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_55(VOID)
{
  DEBUG(("Idt 55\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_56(VOID)
{
  DEBUG(("Idt 56\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_57(VOID)
{
  DEBUG(("Idt 57\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_58(VOID)
{
  DEBUG(("Idt 58\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_59(VOID)
{
  DEBUG(("Idt 59\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_60(VOID)
{
  DEBUG(("Idt 60\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_61(VOID)
{
  DEBUG(("Idt 61\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_62(VOID)
{
  DEBUG(("Idt 62\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_63(VOID)
{
  DEBUG(("Idt 63\n"));
  __asm__ __volatile__ ("iretq");
}
#elif XBLOCK == 2
VOID
Fidt_64(VOID)
{
  DEBUG(("Idt 64\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_65(VOID)
{
  DEBUG(("Idt 65\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_66(VOID)
{
  DEBUG(("Idt 66\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_67(VOID)
{
  DEBUG(("Idt 67\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_68(VOID)
{
  DEBUG(("Idt 68\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_69(VOID)
{
  DEBUG(("Idt 69\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_70(VOID)
{
  DEBUG(("Idt 70\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_71(VOID)
{
  DEBUG(("Idt 71\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_72(VOID)
{
  DEBUG(("Idt 72\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_73(VOID)
{
  DEBUG(("Idt 73\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_74(VOID)
{
  DEBUG(("Idt 74\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_75(VOID)
{
  DEBUG(("Idt 75\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_76(VOID)
{
  DEBUG(("Idt 76\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_77(VOID)
{
  DEBUG(("Idt 77\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_78(VOID)
{
  DEBUG(("Idt 78\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_79(VOID)
{
  DEBUG(("Idt 79\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_80(VOID)
{
  DEBUG(("Idt 80\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_81(VOID)
{
  DEBUG(("Idt 81\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_82(VOID)
{
  DEBUG(("Idt 82\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_83(VOID)
{
  DEBUG(("Idt 83\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_84(VOID)
{
  DEBUG(("Idt 84\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_85(VOID)
{
  DEBUG(("Idt 85\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_86(VOID)
{
  DEBUG(("Idt 86\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_87(VOID)
{
  DEBUG(("Idt 87\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_88(VOID)
{
  DEBUG(("Idt 88\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_89(VOID)
{
  DEBUG(("Idt 89\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_90(VOID)
{
  DEBUG(("Idt 90\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_91(VOID)
{
  DEBUG(("Idt 91\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_92(VOID)
{
  DEBUG(("Idt 92\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_93(VOID)
{
  DEBUG(("Idt 93\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_94(VOID)
{
  DEBUG(("Idt 94\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_95(VOID)
{
  DEBUG(("Idt 95\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_96(VOID)
{
  DEBUG(("Idt 96\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_97(VOID)
{
  DEBUG(("Idt 97\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_98(VOID)
{
  DEBUG(("Idt 98\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_99(VOID)
{
  DEBUG(("Idt 99\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_100(VOID)
{
  DEBUG(("Idt 100\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_101(VOID)
{
  DEBUG(("Idt 101\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_102(VOID)
{
  DEBUG(("Idt 102\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_103(VOID)
{
  DEBUG(("Idt 103\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_104(VOID)
{
  DEBUG(("Idt 104\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_105(VOID)
{
  DEBUG(("Idt 105\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_106(VOID)
{
  DEBUG(("Idt 106\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_107(VOID)
{
  DEBUG(("Idt 107\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_108(VOID)
{
  DEBUG(("Idt 108\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_109(VOID)
{
  DEBUG(("Idt 109\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_110(VOID)
{
  DEBUG(("Idt 110\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_111(VOID)
{
  DEBUG(("Idt 111\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_112(VOID)
{
  DEBUG(("Idt 112\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_113(VOID)
{
  DEBUG(("Idt 113\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_114(VOID)
{
  DEBUG(("Idt 114\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_115(VOID)
{
  DEBUG(("Idt 115\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_116(VOID)
{
  DEBUG(("Idt 116\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_117(VOID)
{
  DEBUG(("Idt 117\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_118(VOID)
{
  DEBUG(("Idt 118\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_119(VOID)
{
  DEBUG(("Idt 119\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_120(VOID)
{
  DEBUG(("Idt 120\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_121(VOID)
{
  DEBUG(("Idt 121\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_122(VOID)
{
  DEBUG(("Idt 122\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_123(VOID)
{
  DEBUG(("Idt 123\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_124(VOID)
{
  DEBUG(("Idt 124\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_125(VOID)
{
  DEBUG(("Idt 125\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_126(VOID)
{
  DEBUG(("Idt 126\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_127(VOID)
{
  DEBUG(("Idt 127\n"));
  __asm__ __volatile__ ("iretq");
}
#elif XBLOCK == 3
VOID
Fidt_128(VOID)
{
  DEBUG(("Idt 128\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_129(VOID)
{
  DEBUG(("Idt 129\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_130(VOID)
{
  DEBUG(("Idt 130\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_131(VOID)
{
  DEBUG(("Idt 131\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_132(VOID)
{
  DEBUG(("Idt 132\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_133(VOID)
{
  DEBUG(("Idt 133\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_134(VOID)
{
  DEBUG(("Idt 134\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_135(VOID)
{
  DEBUG(("Idt 135\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_136(VOID)
{
  DEBUG(("Idt 136\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_137(VOID)
{
  DEBUG(("Idt 137\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_138(VOID)
{
  DEBUG(("Idt 138\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_139(VOID)
{
  DEBUG(("Idt 139\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_140(VOID)
{
  DEBUG(("Idt 140\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_141(VOID)
{
  DEBUG(("Idt 141\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_142(VOID)
{
  DEBUG(("Idt 142\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_143(VOID)
{
  DEBUG(("Idt 143\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_144(VOID)
{
  DEBUG(("Idt 144\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_145(VOID)
{
  DEBUG(("Idt 145\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_146(VOID)
{
  DEBUG(("Idt 146\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_147(VOID)
{
  DEBUG(("Idt 147\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_148(VOID)
{
  DEBUG(("Idt 148\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_149(VOID)
{
  DEBUG(("Idt 149\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_150(VOID)
{
  DEBUG(("Idt 150\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_151(VOID)
{
  DEBUG(("Idt 151\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_152(VOID)
{
  DEBUG(("Idt 152\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_153(VOID)
{
  DEBUG(("Idt 153\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_154(VOID)
{
  DEBUG(("Idt 154\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_155(VOID)
{
  DEBUG(("Idt 155\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_156(VOID)
{
  DEBUG(("Idt 156\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_157(VOID)
{
  DEBUG(("Idt 157\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_158(VOID)
{
  DEBUG(("Idt 158\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_159(VOID)
{
  DEBUG(("Idt 159\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_160(VOID)
{
  DEBUG(("Idt 160\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_161(VOID)
{
  DEBUG(("Idt 161\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_162(VOID)
{
  DEBUG(("Idt 162\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_163(VOID)
{
  DEBUG(("Idt 163\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_164(VOID)
{
  DEBUG(("Idt 164\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_165(VOID)
{
  DEBUG(("Idt 165\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_166(VOID)
{
  DEBUG(("Idt 166\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_167(VOID)
{
  DEBUG(("Idt 167\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_168(VOID)
{
  DEBUG(("Idt 168\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_169(VOID)
{
  DEBUG(("Idt 169\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_170(VOID)
{
  DEBUG(("Idt 170\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_171(VOID)
{
  DEBUG(("Idt 171\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_172(VOID)
{
  DEBUG(("Idt 172\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_173(VOID)
{
  DEBUG(("Idt 173\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_174(VOID)
{
  DEBUG(("Idt 174\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_175(VOID)
{
  DEBUG(("Idt 175\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_176(VOID)
{
  DEBUG(("Idt 176\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_177(VOID)
{
  DEBUG(("Idt 177\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_178(VOID)
{
  DEBUG(("Idt 178\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_179(VOID)
{
  DEBUG(("Idt 179\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_180(VOID)
{
  DEBUG(("Idt 180\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_181(VOID)
{
  DEBUG(("Idt 181\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_182(VOID)
{
  DEBUG(("Idt 182\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_183(VOID)
{
  DEBUG(("Idt 183\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_184(VOID)
{
  DEBUG(("Idt 184\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_185(VOID)
{
  DEBUG(("Idt 185\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_186(VOID)
{
  DEBUG(("Idt 186\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_187(VOID)
{
  DEBUG(("Idt 187\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_188(VOID)
{
  DEBUG(("Idt 188\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_189(VOID)
{
  DEBUG(("Idt 189\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_190(VOID)
{
  DEBUG(("Idt 190\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_191(VOID)
{
  DEBUG(("Idt 191\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_192(VOID)
{
  DEBUG(("Idt 192\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_193(VOID)
{
  DEBUG(("Idt 193\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_194(VOID)
{
  DEBUG(("Idt 194\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_195(VOID)
{
  DEBUG(("Idt 195\n"));
  __asm__ __volatile__ ("iretq");
}
#elif XBLOCK == 4
VOID
Fidt_196(VOID)
{
  DEBUG(("Idt 196\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_197(VOID)
{
  DEBUG(("Idt 197\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_198(VOID)
{
  DEBUG(("Idt 198\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_199(VOID)
{
  DEBUG(("Idt 199\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_200(VOID)
{
  DEBUG(("Idt 200\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_201(VOID)
{
  DEBUG(("Idt 201\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_202(VOID)
{
  DEBUG(("Idt 202\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_203(VOID)
{
  DEBUG(("Idt 203\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_204(VOID)
{
  DEBUG(("Idt 204\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_205(VOID)
{
  DEBUG(("Idt 205\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_206(VOID)
{
  DEBUG(("Idt 206\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_207(VOID)
{
  DEBUG(("Idt 207\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_208(VOID)
{
  DEBUG(("Idt 208\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_209(VOID)
{
  DEBUG(("Idt 209\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_210(VOID)
{
  DEBUG(("Idt 210\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_211(VOID)
{
  DEBUG(("Idt 211\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_212(VOID)
{
  DEBUG(("Idt 212\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_213(VOID)
{
  DEBUG(("Idt 213\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_214(VOID)
{
  DEBUG(("Idt 214\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_215(VOID)
{
  DEBUG(("Idt 215\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_216(VOID)
{
  DEBUG(("Idt 216\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_217(VOID)
{
  DEBUG(("Idt 217\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_218(VOID)
{
  DEBUG(("Idt 218\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_219(VOID)
{
  DEBUG(("Idt 219\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_220(VOID)
{
  DEBUG(("Idt 220\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_221(VOID)
{
  DEBUG(("Idt 221\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_222(VOID)
{
  DEBUG(("Idt 222\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_223(VOID)
{
  DEBUG(("Idt 223\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_224(VOID)
{
  DEBUG(("Idt 224\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_225(VOID)
{
  DEBUG(("Idt 225\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_226(VOID)
{
  DEBUG(("Idt 226\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_227(VOID)
{
  DEBUG(("Idt 227\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_228(VOID)
{
  DEBUG(("Idt 228\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_229(VOID)
{
  DEBUG(("Idt 229\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_230(VOID)
{
  DEBUG(("Idt 230\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_231(VOID)
{
  DEBUG(("Idt 231\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_232(VOID)
{
  DEBUG(("Idt 232\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_233(VOID)
{
  DEBUG(("Idt 233\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_234(VOID)
{
  DEBUG(("Idt 234\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_235(VOID)
{
  DEBUG(("Idt 235\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_236(VOID)
{
  DEBUG(("Idt 236\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_237(VOID)
{
  DEBUG(("Idt 237\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_238(VOID)
{
  DEBUG(("Idt 238\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_239(VOID)
{
  DEBUG(("Idt 239\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_240(VOID)
{
  DEBUG(("Idt 240\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_241(VOID)
{
  DEBUG(("Idt 241\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_242(VOID)
{
  DEBUG(("Idt 242\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_243(VOID)
{
  DEBUG(("Idt 243\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_244(VOID)
{
  DEBUG(("Idt 244\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_245(VOID)
{
  DEBUG(("Idt 245\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_246(VOID)
{
  DEBUG(("Idt 246\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_247(VOID)
{
  DEBUG(("Idt 247\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_248(VOID)
{
  DEBUG(("Idt 248\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_249(VOID)
{
  DEBUG(("Idt 249\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_250(VOID)
{
  DEBUG(("Idt 250\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_251(VOID)
{
  DEBUG(("Idt 251\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_252(VOID)
{
  DEBUG(("Idt 252\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_253(VOID)
{
  DEBUG(("Idt 253\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_254(VOID)
{
  DEBUG(("Idt 254\n"));
  __asm__ __volatile__ ("iretq");
}
VOID
Fidt_255(VOID)
{
  DEBUG(("Idt 255\n"));
  __asm__ __volatile__ ("iretq");
}
#endif

STATIC VOID
InitFakeIdtEntries(VOID)
{
  IA32_IDT_GATE_DESCRIPTOR  IdtEntry;

  IdtEntry.Bits.Selector     = 0x8;
  IdtEntry.Bits.Reserved_0   = 0;
  IdtEntry.Bits.GateType     = IA32_IDT_GATE_TYPE_INTERRUPT_32;
  IdtEntry.Bits.OffsetUpper  = 0;

#if XBLOCK == 1
  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_0;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_0) >> 16);
  CopyMem(&mIdtEntries[0], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_1;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_1) >> 16);
  CopyMem(&mIdtEntries[1], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_2;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_2) >> 16);
  CopyMem(&mIdtEntries[2], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_3;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_3) >> 16);
  CopyMem(&mIdtEntries[3], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_4;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_4) >> 16);
  CopyMem(&mIdtEntries[4], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_5;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_5) >> 16);
  CopyMem(&mIdtEntries[5], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_6;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_6) >> 16);
  CopyMem(&mIdtEntries[6], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_7;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_7) >> 16);
  CopyMem(&mIdtEntries[7], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_8;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_8) >> 16);
  CopyMem(&mIdtEntries[8], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_9;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_9) >> 16);
  CopyMem(&mIdtEntries[9], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_10;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_10) >> 16);
  CopyMem(&mIdtEntries[10], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_11;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_11) >> 16);
  CopyMem(&mIdtEntries[11], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_12;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_12) >> 16);
  CopyMem(&mIdtEntries[12], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_13;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_13) >> 16);
  CopyMem(&mIdtEntries[13], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_14;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_14) >> 16);
  CopyMem(&mIdtEntries[14], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_15;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_15) >> 16);
  CopyMem(&mIdtEntries[15], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_16;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_16) >> 16);
  CopyMem(&mIdtEntries[16], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_17;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_17) >> 16);
  CopyMem(&mIdtEntries[17], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_18;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_18) >> 16);
  CopyMem(&mIdtEntries[18], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_19;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_19) >> 16);
  CopyMem(&mIdtEntries[19], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_20;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_20) >> 16);
  CopyMem(&mIdtEntries[20], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_21;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_21) >> 16);
  CopyMem(&mIdtEntries[21], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_22;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_22) >> 16);
  CopyMem(&mIdtEntries[22], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_23;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_23) >> 16);
  CopyMem(&mIdtEntries[23], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_24;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_24) >> 16);
  CopyMem(&mIdtEntries[24], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_25;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_25) >> 16);
  CopyMem(&mIdtEntries[25], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_26;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_26) >> 16);
  CopyMem(&mIdtEntries[26], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_27;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_27) >> 16);
  CopyMem(&mIdtEntries[27], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_28;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_28) >> 16);
  CopyMem(&mIdtEntries[28], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_29;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_29) >> 16);
  CopyMem(&mIdtEntries[29], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_30;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_30) >> 16);
  CopyMem(&mIdtEntries[30], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_31;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_31) >> 16);
  CopyMem(&mIdtEntries[31], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_32;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_32) >> 16);
  CopyMem(&mIdtEntries[32], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_33;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_33) >> 16);
  CopyMem(&mIdtEntries[33], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_34;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_34) >> 16);
  CopyMem(&mIdtEntries[34], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_35;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_35) >> 16);
  CopyMem(&mIdtEntries[35], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_36;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_36) >> 16);
  CopyMem(&mIdtEntries[36], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_37;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_37) >> 16);
  CopyMem(&mIdtEntries[37], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_38;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_38) >> 16);
  CopyMem(&mIdtEntries[38], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_39;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_39) >> 16);
  CopyMem(&mIdtEntries[39], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_40;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_40) >> 16);
  CopyMem(&mIdtEntries[40], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_41;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_41) >> 16);
  CopyMem(&mIdtEntries[41], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_42;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_42) >> 16);
  CopyMem(&mIdtEntries[42], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_43;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_43) >> 16);
  CopyMem(&mIdtEntries[43], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_44;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_44) >> 16);
  CopyMem(&mIdtEntries[44], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_45;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_45) >> 16);
  CopyMem(&mIdtEntries[45], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_46;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_46) >> 16);
  CopyMem(&mIdtEntries[46], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_47;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_47) >> 16);
  CopyMem(&mIdtEntries[47], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_48;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_48) >> 16);
  CopyMem(&mIdtEntries[48], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_49;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_49) >> 16);
  CopyMem(&mIdtEntries[49], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_50;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_50) >> 16);
  CopyMem(&mIdtEntries[50], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_51;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_51) >> 16);
  CopyMem(&mIdtEntries[51], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_52;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_52) >> 16);
  CopyMem(&mIdtEntries[52], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_53;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_53) >> 16);
  CopyMem(&mIdtEntries[53], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_54;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_54) >> 16);
  CopyMem(&mIdtEntries[54], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_55;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_55) >> 16);
  CopyMem(&mIdtEntries[55], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_56;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_56) >> 16);
  CopyMem(&mIdtEntries[56], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_57;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_57) >> 16);
  CopyMem(&mIdtEntries[57], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_58;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_58) >> 16);
  CopyMem(&mIdtEntries[58], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_59;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_59) >> 16);
  CopyMem(&mIdtEntries[59], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_60;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_60) >> 16);
  CopyMem(&mIdtEntries[60], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_61;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_61) >> 16);
  CopyMem(&mIdtEntries[61], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_62;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_62) >> 16);
  CopyMem(&mIdtEntries[62], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_63;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_63) >> 16);
  CopyMem(&mIdtEntries[63], &IdtEntry, sizeof (IdtEntry));

#elif XBLOCK == 2
/*
  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_64;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_64) >> 16);
  CopyMem(&mIdtEntries[64], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_65;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_65) >> 16);
  CopyMem(&mIdtEntries[65], &IdtEntry, sizeof (IdtEntry));
*/

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_66;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_66) >> 16);
  CopyMem(&mIdtEntries[66], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_67;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_67) >> 16);
  CopyMem(&mIdtEntries[67], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_68;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_68) >> 16);
  CopyMem(&mIdtEntries[68], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_69;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_69) >> 16);
  CopyMem(&mIdtEntries[69], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_70;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_70) >> 16);
  CopyMem(&mIdtEntries[70], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_71;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_71) >> 16);
  CopyMem(&mIdtEntries[71], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_72;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_72) >> 16);
  CopyMem(&mIdtEntries[72], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_73;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_73) >> 16);
  CopyMem(&mIdtEntries[73], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_74;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_74) >> 16);
  CopyMem(&mIdtEntries[74], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_75;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_75) >> 16);
  CopyMem(&mIdtEntries[75], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_76;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_76) >> 16);
  CopyMem(&mIdtEntries[76], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_77;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_77) >> 16);
  CopyMem(&mIdtEntries[77], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_78;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_78) >> 16);
  CopyMem(&mIdtEntries[78], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_79;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_79) >> 16);
  CopyMem(&mIdtEntries[79], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_80;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_80) >> 16);
  CopyMem(&mIdtEntries[80], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_81;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_81) >> 16);
  CopyMem(&mIdtEntries[81], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_82;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_82) >> 16);
  CopyMem(&mIdtEntries[82], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_83;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_83) >> 16);
  CopyMem(&mIdtEntries[83], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_84;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_84) >> 16);
  CopyMem(&mIdtEntries[84], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_85;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_85) >> 16);
  CopyMem(&mIdtEntries[85], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_86;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_86) >> 16);
  CopyMem(&mIdtEntries[86], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_87;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_87) >> 16);
  CopyMem(&mIdtEntries[87], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_88;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_88) >> 16);
  CopyMem(&mIdtEntries[88], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_89;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_89) >> 16);
  CopyMem(&mIdtEntries[89], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_90;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_90) >> 16);
  CopyMem(&mIdtEntries[90], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_91;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_91) >> 16);
  CopyMem(&mIdtEntries[91], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_92;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_92) >> 16);
  CopyMem(&mIdtEntries[92], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_93;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_93) >> 16);
  CopyMem(&mIdtEntries[93], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_94;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_94) >> 16);
  CopyMem(&mIdtEntries[94], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_95;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_95) >> 16);
  CopyMem(&mIdtEntries[95], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_96;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_96) >> 16);
  CopyMem(&mIdtEntries[96], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_97;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_97) >> 16);
  CopyMem(&mIdtEntries[97], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_98;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_98) >> 16);
  CopyMem(&mIdtEntries[98], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_99;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_99) >> 16);
  CopyMem(&mIdtEntries[99], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_100;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_100) >> 16);
  CopyMem(&mIdtEntries[100], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_101;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_101) >> 16);
  CopyMem(&mIdtEntries[101], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_102;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_102) >> 16);
  CopyMem(&mIdtEntries[102], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_103;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_103) >> 16);
  CopyMem(&mIdtEntries[103], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_104;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_104) >> 16);
  CopyMem(&mIdtEntries[104], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_105;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_105) >> 16);
  CopyMem(&mIdtEntries[105], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_106;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_106) >> 16);
  CopyMem(&mIdtEntries[106], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_107;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_107) >> 16);
  CopyMem(&mIdtEntries[107], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_108;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_108) >> 16);
  CopyMem(&mIdtEntries[108], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_109;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_109) >> 16);
  CopyMem(&mIdtEntries[109], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_110;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_110) >> 16);
  CopyMem(&mIdtEntries[110], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_111;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_111) >> 16);
  CopyMem(&mIdtEntries[111], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_112;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_112) >> 16);
  CopyMem(&mIdtEntries[112], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_113;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_113) >> 16);
  CopyMem(&mIdtEntries[113], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_114;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_114) >> 16);
  CopyMem(&mIdtEntries[114], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_115;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_115) >> 16);
  CopyMem(&mIdtEntries[115], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_116;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_116) >> 16);
  CopyMem(&mIdtEntries[116], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_117;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_117) >> 16);
  CopyMem(&mIdtEntries[117], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_118;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_118) >> 16);
  CopyMem(&mIdtEntries[118], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_119;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_119) >> 16);
  CopyMem(&mIdtEntries[119], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_120;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_120) >> 16);
  CopyMem(&mIdtEntries[120], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_121;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_121) >> 16);
  CopyMem(&mIdtEntries[121], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_122;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_122) >> 16);
  CopyMem(&mIdtEntries[122], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_123;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_123) >> 16);
  CopyMem(&mIdtEntries[123], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_124;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_124) >> 16);
  CopyMem(&mIdtEntries[124], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_125;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_125) >> 16);
  CopyMem(&mIdtEntries[125], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_126;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_126) >> 16);
  CopyMem(&mIdtEntries[126], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_127;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_127) >> 16);
  CopyMem(&mIdtEntries[127], &IdtEntry, sizeof (IdtEntry));

#elif XBLOCK == 3
  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_128;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_128) >> 16);
  CopyMem(&mIdtEntries[128], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_129;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_129) >> 16);
  CopyMem(&mIdtEntries[129], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_130;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_130) >> 16);
  CopyMem(&mIdtEntries[130], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_131;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_131) >> 16);
  CopyMem(&mIdtEntries[131], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_132;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_132) >> 16);
  CopyMem(&mIdtEntries[132], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_133;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_133) >> 16);
  CopyMem(&mIdtEntries[133], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_134;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_134) >> 16);
  CopyMem(&mIdtEntries[134], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_135;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_135) >> 16);
  CopyMem(&mIdtEntries[135], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_136;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_136) >> 16);
  CopyMem(&mIdtEntries[136], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_137;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_137) >> 16);
  CopyMem(&mIdtEntries[137], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_138;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_138) >> 16);
  CopyMem(&mIdtEntries[138], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_139;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_139) >> 16);
  CopyMem(&mIdtEntries[139], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_140;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_140) >> 16);
  CopyMem(&mIdtEntries[140], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_141;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_141) >> 16);
  CopyMem(&mIdtEntries[141], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_142;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_142) >> 16);
  CopyMem(&mIdtEntries[142], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_143;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_143) >> 16);
  CopyMem(&mIdtEntries[143], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_144;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_144) >> 16);
  CopyMem(&mIdtEntries[144], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_145;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_145) >> 16);
  CopyMem(&mIdtEntries[145], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_146;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_146) >> 16);
  CopyMem(&mIdtEntries[146], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_147;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_147) >> 16);
  CopyMem(&mIdtEntries[147], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_148;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_148) >> 16);
  CopyMem(&mIdtEntries[148], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_149;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_149) >> 16);
  CopyMem(&mIdtEntries[149], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_150;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_150) >> 16);
  CopyMem(&mIdtEntries[150], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_151;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_151) >> 16);
  CopyMem(&mIdtEntries[151], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_152;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_152) >> 16);
  CopyMem(&mIdtEntries[152], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_153;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_153) >> 16);
  CopyMem(&mIdtEntries[153], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_154;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_154) >> 16);
  CopyMem(&mIdtEntries[154], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_155;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_155) >> 16);
  CopyMem(&mIdtEntries[155], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_156;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_156) >> 16);
  CopyMem(&mIdtEntries[156], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_157;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_157) >> 16);
  CopyMem(&mIdtEntries[157], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_158;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_158) >> 16);
  CopyMem(&mIdtEntries[158], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_159;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_159) >> 16);
  CopyMem(&mIdtEntries[159], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_160;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_160) >> 16);
  CopyMem(&mIdtEntries[160], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_161;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_161) >> 16);
  CopyMem(&mIdtEntries[161], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_162;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_162) >> 16);
  CopyMem(&mIdtEntries[162], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_163;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_163) >> 16);
  CopyMem(&mIdtEntries[163], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_164;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_164) >> 16);
  CopyMem(&mIdtEntries[164], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_165;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_165) >> 16);
  CopyMem(&mIdtEntries[165], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_166;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_166) >> 16);
  CopyMem(&mIdtEntries[166], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_167;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_167) >> 16);
  CopyMem(&mIdtEntries[167], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_168;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_168) >> 16);
  CopyMem(&mIdtEntries[168], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_169;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_169) >> 16);
  CopyMem(&mIdtEntries[169], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_170;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_170) >> 16);
  CopyMem(&mIdtEntries[170], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_171;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_171) >> 16);
  CopyMem(&mIdtEntries[171], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_172;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_172) >> 16);
  CopyMem(&mIdtEntries[172], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_173;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_173) >> 16);
  CopyMem(&mIdtEntries[173], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_174;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_174) >> 16);
  CopyMem(&mIdtEntries[174], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_175;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_175) >> 16);
  CopyMem(&mIdtEntries[175], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_176;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_176) >> 16);
  CopyMem(&mIdtEntries[176], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_177;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_177) >> 16);
  CopyMem(&mIdtEntries[177], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_178;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_178) >> 16);
  CopyMem(&mIdtEntries[178], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_179;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_179) >> 16);
  CopyMem(&mIdtEntries[179], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_180;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_180) >> 16);
  CopyMem(&mIdtEntries[180], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_181;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_181) >> 16);
  CopyMem(&mIdtEntries[181], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_182;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_182) >> 16);
  CopyMem(&mIdtEntries[182], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_183;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_183) >> 16);
  CopyMem(&mIdtEntries[183], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_184;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_184) >> 16);
  CopyMem(&mIdtEntries[184], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_185;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_185) >> 16);
  CopyMem(&mIdtEntries[185], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_186;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_186) >> 16);
  CopyMem(&mIdtEntries[186], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_187;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_187) >> 16);
  CopyMem(&mIdtEntries[187], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_188;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_188) >> 16);
  CopyMem(&mIdtEntries[188], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_189;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_189) >> 16);
  CopyMem(&mIdtEntries[189], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_190;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_190) >> 16);
  CopyMem(&mIdtEntries[190], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_191;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_191) >> 16);
  CopyMem(&mIdtEntries[191], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_192;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_192) >> 16);
  CopyMem(&mIdtEntries[192], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_193;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_193) >> 16);
  CopyMem(&mIdtEntries[193], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_194;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_194) >> 16);
  CopyMem(&mIdtEntries[194], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_195;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_195) >> 16);
  CopyMem(&mIdtEntries[195], &IdtEntry, sizeof (IdtEntry));

#elif XBLOCK == 4
  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_196;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_196) >> 16);
  CopyMem(&mIdtEntries[196], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_197;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_197) >> 16);
  CopyMem(&mIdtEntries[197], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_198;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_198) >> 16);
  CopyMem(&mIdtEntries[198], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_199;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_199) >> 16);
  CopyMem(&mIdtEntries[199], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_200;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_200) >> 16);
  CopyMem(&mIdtEntries[200], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_201;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_201) >> 16);
  CopyMem(&mIdtEntries[201], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_202;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_202) >> 16);
  CopyMem(&mIdtEntries[202], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_203;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_203) >> 16);
  CopyMem(&mIdtEntries[203], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_204;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_204) >> 16);
  CopyMem(&mIdtEntries[204], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_205;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_205) >> 16);
  CopyMem(&mIdtEntries[205], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_206;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_206) >> 16);
  CopyMem(&mIdtEntries[206], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_207;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_207) >> 16);
  CopyMem(&mIdtEntries[207], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_208;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_208) >> 16);
  CopyMem(&mIdtEntries[208], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_209;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_209) >> 16);
  CopyMem(&mIdtEntries[209], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_210;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_210) >> 16);
  CopyMem(&mIdtEntries[210], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_211;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_211) >> 16);
  CopyMem(&mIdtEntries[211], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_212;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_212) >> 16);
  CopyMem(&mIdtEntries[212], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_213;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_213) >> 16);
  CopyMem(&mIdtEntries[213], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_214;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_214) >> 16);
  CopyMem(&mIdtEntries[214], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_215;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_215) >> 16);
  CopyMem(&mIdtEntries[215], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_216;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_216) >> 16);
  CopyMem(&mIdtEntries[216], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_217;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_217) >> 16);
  CopyMem(&mIdtEntries[217], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_218;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_218) >> 16);
  CopyMem(&mIdtEntries[218], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_219;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_219) >> 16);
  CopyMem(&mIdtEntries[219], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_220;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_220) >> 16);
  CopyMem(&mIdtEntries[220], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_221;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_221) >> 16);
  CopyMem(&mIdtEntries[221], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_222;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_222) >> 16);
  CopyMem(&mIdtEntries[222], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_223;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_223) >> 16);
  CopyMem(&mIdtEntries[223], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_224;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_224) >> 16);
  CopyMem(&mIdtEntries[224], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_225;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_225) >> 16);
  CopyMem(&mIdtEntries[225], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_226;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_226) >> 16);
  CopyMem(&mIdtEntries[226], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_227;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_227) >> 16);
  CopyMem(&mIdtEntries[227], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_228;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_228) >> 16);
  CopyMem(&mIdtEntries[228], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_229;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_229) >> 16);
  CopyMem(&mIdtEntries[229], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_230;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_230) >> 16);
  CopyMem(&mIdtEntries[230], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_231;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_231) >> 16);
  CopyMem(&mIdtEntries[231], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_232;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_232) >> 16);
  CopyMem(&mIdtEntries[232], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_233;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_233) >> 16);
  CopyMem(&mIdtEntries[233], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_234;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_234) >> 16);
  CopyMem(&mIdtEntries[234], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_235;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_235) >> 16);
  CopyMem(&mIdtEntries[235], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_236;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_236) >> 16);
  CopyMem(&mIdtEntries[236], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_237;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_237) >> 16);
  CopyMem(&mIdtEntries[237], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_238;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_238) >> 16);
  CopyMem(&mIdtEntries[238], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_239;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_239) >> 16);
  CopyMem(&mIdtEntries[239], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_240;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_240) >> 16);
  CopyMem(&mIdtEntries[240], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_241;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_241) >> 16);
  CopyMem(&mIdtEntries[241], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_242;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_242) >> 16);
  CopyMem(&mIdtEntries[242], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_243;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_243) >> 16);
  CopyMem(&mIdtEntries[243], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_244;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_244) >> 16);
  CopyMem(&mIdtEntries[244], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_245;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_245) >> 16);
  CopyMem(&mIdtEntries[245], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_246;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_246) >> 16);
  CopyMem(&mIdtEntries[246], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_247;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_247) >> 16);
  CopyMem(&mIdtEntries[247], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_248;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_248) >> 16);
  CopyMem(&mIdtEntries[248], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_249;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_249) >> 16);
  CopyMem(&mIdtEntries[249], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_250;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_250) >> 16);
  CopyMem(&mIdtEntries[250], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_251;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_251) >> 16);
  CopyMem(&mIdtEntries[251], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_252;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_252) >> 16);
  CopyMem(&mIdtEntries[252], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_253;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_253) >> 16);
  CopyMem(&mIdtEntries[253], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_254;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_254) >> 16);
  CopyMem(&mIdtEntries[254], &IdtEntry, sizeof (IdtEntry));

  IdtEntry.Bits.OffsetLow    = (UINT16)(UINTN)Fidt_255;
  IdtEntry.Bits.OffsetHigh   = (UINT16)(((UINTN)Fidt_255) >> 16);
  CopyMem(&mIdtEntries[255], &IdtEntry, sizeof (IdtEntry));
#endif
}

 
