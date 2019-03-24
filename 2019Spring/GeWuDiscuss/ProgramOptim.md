# Program Optimizations

**Yimin Gu**

**2019.3**

[TOC]

Ref：《深入理解计算机系统》

部分图片和内容来自吴俊敏计算机系统详解课程PPT

![180797](C:\Users\petergu\Downloads\180797.jpg)

## Previous

### Turning C into Object Code

`gcc –O1 p1.c p2.c -o p`

Compile file p1.c and p2.c into executable file p, using basic optimization.

![1552813158163](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552813158163.png)

### Assembly & Memory layout(x86-64 Linux)

![1552813449948](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552813449948.png)

![1552813331389](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552813331389.png)

**Move, Arithmetic, Condition codes and jumping, (Jump table), Control flow, ...**

**A simple example to show these**

Source code, compile with `gcc -g`

```c
int a, b, c, d;
double aa, bb, cc, dd;

void arith()
{
	c = a + b;
	d = a << b;
	cc = aa * bb;
	dd = aa / bb;
}
int pointers(int* pa, int* pb)
{
	c = *pa;
	return c;
}
int function(int a, int b)
{
	arith();
	pointers(&a, &b);
	return 0x50;
}
int loop()
{
	int i;
	int sum = 0;
	for(i = 0; i < 100; i++)
		sum += i;
	return sum;
}
int condition(int a)
{
	if(a > 0)
		b = 1;
	else if(a < -1)
		b = 1;
	else
		b = 0;
	return b;
}
int main()
{
	return 0;
}
```

Full output of `objdump -dS`(Don't be afraid, only some parts are useful for us), a.out compiled with no optimization. 

```assembly

a.out:     file format elf64-x86-64


Disassembly of section .init:

00000000000004b8 <_init>:
 4b8:	48 83 ec 08          	sub    $0x8,%rsp
 4bc:	48 8b 05 25 0b 20 00 	mov    0x200b25(%rip),%rax        # 200fe8 <__gmon_start__>
 4c3:	48 85 c0             	test   %rax,%rax
 4c6:	74 02                	je     4ca <_init+0x12>
 4c8:	ff d0                	callq  *%rax
 4ca:	48 83 c4 08          	add    $0x8,%rsp
 4ce:	c3                   	retq   

Disassembly of section .plt:

00000000000004d0 <.plt>:
 4d0:	ff 35 f2 0a 20 00    	pushq  0x200af2(%rip)        # 200fc8 <_GLOBAL_OFFSET_TABLE_+0x8>
 4d6:	ff 25 f4 0a 20 00    	jmpq   *0x200af4(%rip)        # 200fd0 <_GLOBAL_OFFSET_TABLE_+0x10>
 4dc:	0f 1f 40 00          	nopl   0x0(%rax)

Disassembly of section .plt.got:

00000000000004e0 <__cxa_finalize@plt>:
 4e0:	ff 25 12 0b 20 00    	jmpq   *0x200b12(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 4e6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000000004f0 <_start>:
 4f0:	31 ed                	xor    %ebp,%ebp
 4f2:	49 89 d1             	mov    %rdx,%r9
 4f5:	5e                   	pop    %rsi
 4f6:	48 89 e2             	mov    %rsp,%rdx
 4f9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
 4fd:	50                   	push   %rax
 4fe:	54                   	push   %rsp
 4ff:	4c 8d 05 9a 02 00 00 	lea    0x29a(%rip),%r8        # 7a0 <__libc_csu_fini>
 506:	48 8d 0d 23 02 00 00 	lea    0x223(%rip),%rcx        # 730 <__libc_csu_init>
 50d:	48 8d 3d 09 02 00 00 	lea    0x209(%rip),%rdi        # 71d <main>
 514:	ff 15 c6 0a 20 00    	callq  *0x200ac6(%rip)        # 200fe0 <__libc_start_main@GLIBC_2.2.5>
 51a:	f4                   	hlt    
 51b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000000520 <deregister_tm_clones>:
 520:	48 8d 3d e9 0a 20 00 	lea    0x200ae9(%rip),%rdi        # 201010 <__TMC_END__>
 527:	55                   	push   %rbp
 528:	48 8d 05 e1 0a 20 00 	lea    0x200ae1(%rip),%rax        # 201010 <__TMC_END__>
 52f:	48 39 f8             	cmp    %rdi,%rax
 532:	48 89 e5             	mov    %rsp,%rbp
 535:	74 19                	je     550 <deregister_tm_clones+0x30>
 537:	48 8b 05 9a 0a 20 00 	mov    0x200a9a(%rip),%rax        # 200fd8 <_ITM_deregisterTMCloneTable>
 53e:	48 85 c0             	test   %rax,%rax
 541:	74 0d                	je     550 <deregister_tm_clones+0x30>
 543:	5d                   	pop    %rbp
 544:	ff e0                	jmpq   *%rax
 546:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 54d:	00 00 00 
 550:	5d                   	pop    %rbp
 551:	c3                   	retq   
 552:	0f 1f 40 00          	nopl   0x0(%rax)
 556:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 55d:	00 00 00 

0000000000000560 <register_tm_clones>:
 560:	48 8d 3d a9 0a 20 00 	lea    0x200aa9(%rip),%rdi        # 201010 <__TMC_END__>
 567:	48 8d 35 a2 0a 20 00 	lea    0x200aa2(%rip),%rsi        # 201010 <__TMC_END__>
 56e:	55                   	push   %rbp
 56f:	48 29 fe             	sub    %rdi,%rsi
 572:	48 89 e5             	mov    %rsp,%rbp
 575:	48 c1 fe 03          	sar    $0x3,%rsi
 579:	48 89 f0             	mov    %rsi,%rax
 57c:	48 c1 e8 3f          	shr    $0x3f,%rax
 580:	48 01 c6             	add    %rax,%rsi
 583:	48 d1 fe             	sar    %rsi
 586:	74 18                	je     5a0 <register_tm_clones+0x40>
 588:	48 8b 05 61 0a 20 00 	mov    0x200a61(%rip),%rax        # 200ff0 <_ITM_registerTMCloneTable>
 58f:	48 85 c0             	test   %rax,%rax
 592:	74 0c                	je     5a0 <register_tm_clones+0x40>
 594:	5d                   	pop    %rbp
 595:	ff e0                	jmpq   *%rax
 597:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 59e:	00 00 
 5a0:	5d                   	pop    %rbp
 5a1:	c3                   	retq   
 5a2:	0f 1f 40 00          	nopl   0x0(%rax)
 5a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 5ad:	00 00 00 

00000000000005b0 <__do_global_dtors_aux>:
 5b0:	80 3d 59 0a 20 00 00 	cmpb   $0x0,0x200a59(%rip)        # 201010 <__TMC_END__>
 5b7:	75 2f                	jne    5e8 <__do_global_dtors_aux+0x38>
 5b9:	48 83 3d 37 0a 20 00 	cmpq   $0x0,0x200a37(%rip)        # 200ff8 <__cxa_finalize@GLIBC_2.2.5>
 5c0:	00 
 5c1:	55                   	push   %rbp
 5c2:	48 89 e5             	mov    %rsp,%rbp
 5c5:	74 0c                	je     5d3 <__do_global_dtors_aux+0x23>
 5c7:	48 8b 3d 3a 0a 20 00 	mov    0x200a3a(%rip),%rdi        # 201008 <__dso_handle>
 5ce:	e8 0d ff ff ff       	callq  4e0 <__cxa_finalize@plt>
 5d3:	e8 48 ff ff ff       	callq  520 <deregister_tm_clones>
 5d8:	c6 05 31 0a 20 00 01 	movb   $0x1,0x200a31(%rip)        # 201010 <__TMC_END__>
 5df:	5d                   	pop    %rbp
 5e0:	c3                   	retq   
 5e1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 5e8:	f3 c3                	repz retq 
 5ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000005f0 <frame_dummy>:
 5f0:	55                   	push   %rbp
 5f1:	48 89 e5             	mov    %rsp,%rbp
 5f4:	5d                   	pop    %rbp
 5f5:	e9 66 ff ff ff       	jmpq   560 <register_tm_clones>

00000000000005fa <arith>:
int a, b, c, d;
double aa, bb, cc, dd;

void arith()
{
 5fa:	55                   	push   %rbp
 5fb:	48 89 e5             	mov    %rsp,%rbp
//	int a, b, c, d;
	c = a + b;
 5fe:	8b 15 30 0a 20 00    	mov    0x200a30(%rip),%edx        # 201034 <a>
 604:	8b 05 12 0a 20 00    	mov    0x200a12(%rip),%eax        # 20101c <b>
 60a:	01 d0                	add    %edx,%eax
 60c:	89 05 1e 0a 20 00    	mov    %eax,0x200a1e(%rip)        # 201030 <c>
	d = a << b;
 612:	8b 15 1c 0a 20 00    	mov    0x200a1c(%rip),%edx        # 201034 <a>
 618:	8b 05 fe 09 20 00    	mov    0x2009fe(%rip),%eax        # 20101c <b>
 61e:	89 c1                	mov    %eax,%ecx
 620:	d3 e2                	shl    %cl,%edx
 622:	89 d0                	mov    %edx,%eax
 624:	89 05 ee 09 20 00    	mov    %eax,0x2009ee(%rip)        # 201018 <d>
//	double aa, bb, cc, dd;
	cc = aa * bb;
 62a:	f2 0f 10 0d ee 09 20 	movsd  0x2009ee(%rip),%xmm1        # 201020 <aa>
 631:	00 
 632:	f2 0f 10 05 ee 09 20 	movsd  0x2009ee(%rip),%xmm0        # 201028 <bb>
 639:	00 
 63a:	f2 0f 59 c1          	mulsd  %xmm1,%xmm0
 63e:	f2 0f 11 05 f2 09 20 	movsd  %xmm0,0x2009f2(%rip)        # 201038 <cc>
 645:	00 
	dd = aa / bb;
 646:	f2 0f 10 05 d2 09 20 	movsd  0x2009d2(%rip),%xmm0        # 201020 <aa>
 64d:	00 
 64e:	f2 0f 10 0d d2 09 20 	movsd  0x2009d2(%rip),%xmm1        # 201028 <bb>
 655:	00 
 656:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
 65a:	f2 0f 11 05 de 09 20 	movsd  %xmm0,0x2009de(%rip)        # 201040 <dd>
 661:	00 
}
 662:	90                   	nop
 663:	5d                   	pop    %rbp
 664:	c3                   	retq   

0000000000000665 <pointers>:
int pointers(int* pa, int* pb)
{
 665:	55                   	push   %rbp
 666:	48 89 e5             	mov    %rsp,%rbp
 669:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
 66d:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
	c = *pa;
 671:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
 675:	8b 00                	mov    (%rax),%eax
 677:	89 05 b3 09 20 00    	mov    %eax,0x2009b3(%rip)        # 201030 <c>
	return c;
 67d:	8b 05 ad 09 20 00    	mov    0x2009ad(%rip),%eax        # 201030 <c>
}
 683:	5d                   	pop    %rbp
 684:	c3                   	retq   

0000000000000685 <function>:
int function(int a, int b)
{
 685:	55                   	push   %rbp
 686:	48 89 e5             	mov    %rsp,%rbp
 689:	48 83 ec 08          	sub    $0x8,%rsp
 68d:	89 7d fc             	mov    %edi,-0x4(%rbp)
 690:	89 75 f8             	mov    %esi,-0x8(%rbp)
	arith();
 693:	b8 00 00 00 00       	mov    $0x0,%eax
 698:	e8 5d ff ff ff       	callq  5fa <arith>
	pointers(&a, &b);
 69d:	48 8d 55 f8          	lea    -0x8(%rbp),%rdx
 6a1:	48 8d 45 fc          	lea    -0x4(%rbp),%rax
 6a5:	48 89 d6             	mov    %rdx,%rsi
 6a8:	48 89 c7             	mov    %rax,%rdi
 6ab:	e8 b5 ff ff ff       	callq  665 <pointers>
	return 0x50;
 6b0:	b8 50 00 00 00       	mov    $0x50,%eax
}
 6b5:	c9                   	leaveq 
 6b6:	c3                   	retq   

00000000000006b7 <loop>:
int loop()
{
 6b7:	55                   	push   %rbp
 6b8:	48 89 e5             	mov    %rsp,%rbp
	int i;
	int sum = 0;
 6bb:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
	for(i = 0; i < 100; i++)
 6c2:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
 6c9:	eb 0a                	jmp    6d5 <loop+0x1e>
		sum += i;
 6cb:	8b 45 f8             	mov    -0x8(%rbp),%eax
 6ce:	01 45 fc             	add    %eax,-0x4(%rbp)
	for(i = 0; i < 100; i++)
 6d1:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
 6d5:	83 7d f8 63          	cmpl   $0x63,-0x8(%rbp)
 6d9:	7e f0                	jle    6cb <loop+0x14>
	return sum;
 6db:	8b 45 fc             	mov    -0x4(%rbp),%eax
}
 6de:	5d                   	pop    %rbp
 6df:	c3                   	retq   

00000000000006e0 <condition>:
int condition(int a)
{
 6e0:	55                   	push   %rbp
 6e1:	48 89 e5             	mov    %rsp,%rbp
 6e4:	89 7d fc             	mov    %edi,-0x4(%rbp)
	if(a > 0)
 6e7:	83 7d fc 00          	cmpl   $0x0,-0x4(%rbp)
 6eb:	7e 0c                	jle    6f9 <condition+0x19>
		b = 1;
 6ed:	c7 05 25 09 20 00 01 	movl   $0x1,0x200925(%rip)        # 20101c <b>
 6f4:	00 00 00 
 6f7:	eb 1c                	jmp    715 <condition+0x35>
	else if(a < -1)
 6f9:	83 7d fc ff          	cmpl   $0xffffffff,-0x4(%rbp)
 6fd:	7d 0c                	jge    70b <condition+0x2b>
		b = 1;
 6ff:	c7 05 13 09 20 00 01 	movl   $0x1,0x200913(%rip)        # 20101c <b>
 706:	00 00 00 
 709:	eb 0a                	jmp    715 <condition+0x35>
	else
		b = 0;
 70b:	c7 05 07 09 20 00 00 	movl   $0x0,0x200907(%rip)        # 20101c <b>
 712:	00 00 00 
	return b;
 715:	8b 05 01 09 20 00    	mov    0x200901(%rip),%eax        # 20101c <b>
}
 71b:	5d                   	pop    %rbp
 71c:	c3                   	retq   

000000000000071d <main>:
int main()
{
 71d:	55                   	push   %rbp
 71e:	48 89 e5             	mov    %rsp,%rbp
	return 0;
 721:	b8 00 00 00 00       	mov    $0x0,%eax
}
 726:	5d                   	pop    %rbp
 727:	c3                   	retq   
 728:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 72f:	00 

0000000000000730 <__libc_csu_init>:
 730:	41 57                	push   %r15
 732:	41 56                	push   %r14
 734:	49 89 d7             	mov    %rdx,%r15
 737:	41 55                	push   %r13
 739:	41 54                	push   %r12
 73b:	4c 8d 25 ae 06 20 00 	lea    0x2006ae(%rip),%r12        # 200df0 <__frame_dummy_init_array_entry>
 742:	55                   	push   %rbp
 743:	48 8d 2d ae 06 20 00 	lea    0x2006ae(%rip),%rbp        # 200df8 <__init_array_end>
 74a:	53                   	push   %rbx
 74b:	41 89 fd             	mov    %edi,%r13d
 74e:	49 89 f6             	mov    %rsi,%r14
 751:	4c 29 e5             	sub    %r12,%rbp
 754:	48 83 ec 08          	sub    $0x8,%rsp
 758:	48 c1 fd 03          	sar    $0x3,%rbp
 75c:	e8 57 fd ff ff       	callq  4b8 <_init>
 761:	48 85 ed             	test   %rbp,%rbp
 764:	74 20                	je     786 <__libc_csu_init+0x56>
 766:	31 db                	xor    %ebx,%ebx
 768:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 76f:	00 
 770:	4c 89 fa             	mov    %r15,%rdx
 773:	4c 89 f6             	mov    %r14,%rsi
 776:	44 89 ef             	mov    %r13d,%edi
 779:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
 77d:	48 83 c3 01          	add    $0x1,%rbx
 781:	48 39 dd             	cmp    %rbx,%rbp
 784:	75 ea                	jne    770 <__libc_csu_init+0x40>
 786:	48 83 c4 08          	add    $0x8,%rsp
 78a:	5b                   	pop    %rbx
 78b:	5d                   	pop    %rbp
 78c:	41 5c                	pop    %r12
 78e:	41 5d                	pop    %r13
 790:	41 5e                	pop    %r14
 792:	41 5f                	pop    %r15
 794:	c3                   	retq   
 795:	90                   	nop
 796:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 79d:	00 00 00 

00000000000007a0 <__libc_csu_fini>:
 7a0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000000007a4 <_fini>:
 7a4:	48 83 ec 08          	sub    $0x8,%rsp
 7a8:	48 83 c4 08          	add    $0x8,%rsp
 7ac:	c3                   	retq   
```



## Chap. 5 Code Optimization

### General useful optimizations

​	You or **the compiler** should do regardless of processor/compiler

- **Compiler Flags**

​	Previous assembly demo program compiled with -O1:


```assembly
00000000000005fa <arith>:
 5fa:	8b 05 34 0a 20 00    	mov    0x200a34(%rip),%eax        # 201034 <a>
 600:	8b 0d 16 0a 20 00    	mov    0x200a16(%rip),%ecx        # 20101c <b>
 606:	8d 14 08             	lea    (%rax,%rcx,1),%edx
 609:	89 15 21 0a 20 00    	mov    %edx,0x200a21(%rip)        # 201030 <c>
 60f:	d3 e0                	shl    %cl,%eax
 611:	89 05 01 0a 20 00    	mov    %eax,0x200a01(%rip)        # 201018 <d>
 617:	f2 0f 10 05 01 0a 20 	movsd  0x200a01(%rip),%xmm0        # 201020 <aa>
 61e:	00 
 61f:	f2 0f 10 0d 01 0a 20 	movsd  0x200a01(%rip),%xmm1        # 201028 <bb>
 626:	00 
 627:	66 0f 28 d0          	movapd %xmm0,%xmm2
 62b:	f2 0f 59 d1          	mulsd  %xmm1,%xmm2
 62f:	f2 0f 11 15 01 0a 20 	movsd  %xmm2,0x200a01(%rip)        # 201038 <cc>
 636:	00 
 637:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
 63b:	f2 0f 11 05 fd 09 20 	movsd  %xmm0,0x2009fd(%rip)        # 201040 <dd>
 642:	00 
 643:	c3                   	retq   

0000000000000644 <pointers>:
 644:	8b 07                	mov    (%rdi),%eax
 646:	89 05 e4 09 20 00    	mov    %eax,0x2009e4(%rip)        # 201030 <c>
 64c:	c3                   	retq   

000000000000064d <function>:
 64d:	53                   	push   %rbx
 64e:	89 fb                	mov    %edi,%ebx
 650:	b8 00 00 00 00       	mov    $0x0,%eax
 655:	e8 a0 ff ff ff       	callq  5fa <arith>
 65a:	89 1d d0 09 20 00    	mov    %ebx,0x2009d0(%rip)        # 201030 <c>
 660:	b8 50 00 00 00       	mov    $0x50,%eax
 665:	5b                   	pop    %rbx
 666:	c3                   	retq   

0000000000000667 <loop>:
 667:	b8 64 00 00 00       	mov    $0x64,%eax
 66c:	83 e8 01             	sub    $0x1,%eax
 66f:	75 fb                	jne    66c <loop+0x5>
 671:	b8 56 13 00 00       	mov    $0x1356,%eax
 676:	c3                   	retq   

0000000000000677 <condition>:
 677:	85 ff                	test   %edi,%edi
 679:	7e 11                	jle    68c <condition+0x15>
 67b:	c7 05 97 09 20 00 01 	movl   $0x1,0x200997(%rip)        # 20101c <b>
 682:	00 00 00 
 685:	8b 05 91 09 20 00    	mov    0x200991(%rip),%eax        # 20101c <b>
 68b:	c3                   	retq   
 68c:	83 ff ff             	cmp    $0xffffffff,%edi
 68f:	0f 9c c0             	setl   %al
 692:	0f b6 c0             	movzbl %al,%eax
 695:	89 05 81 09 20 00    	mov    %eax,0x200981(%rip)        # 20101c <b>
 69b:	eb e8                	jmp    685 <condition+0xe>

000000000000069d <main>:
 69d:	b8 00 00 00 00       	mov    $0x0,%eax
 6a2:	c3                   	retq   
 6a3:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 6aa:	00 00 00 
 6ad:	0f 1f 00             	nopl   (%rax)
```


- **Code Motion** 

  - Reduce frequency with which computation performed:
    - If it will always produce same result
    - Especially moving code out of loop

  ```c
    void set_row(double *a, double *b, long i, long n)
    {
    	long j;
    	for(j = 0; j < n; j++)
    		a[n * i + j] = b[j];
    }
  ```

  `gcc -Og` version: n*j calculated each loop (line 0x7, 0xa)

  ```assembly
    0000000000000000 <set_row>:
       0:   b8 00 00 00 00          mov    $0x0,%eax
       5:   eb 19                   jmp    20 <set_row+0x20>
       7:   49 89 c8                mov    %rcx,%r8
       a:   4c 0f af c2             imul   %rdx,%r8
       e:   49 01 c0                add    %rax,%r8
      11:   f2 0f 10 04 c6          movsd  (%rsi,%rax,8),%xmm0
      16:   f2 42 0f 11 04 c7       movsd  %xmm0,(%rdi,%r8,8)
      1c:   48 83 c0 01             add    $0x1,%rax
      20:   48 39 c8                cmp    %rcx,%rax
      23:   7c e2                   jl     7 <set_row+0x7>
      25:   f3 c3                   repz retq
    
  ```

  gcc -O1 version: n*j calculated only once, stored in %rdx (line 0x5, 0x9)

  ```assembly
  0000000000000000 <set_row>:
     0:   48 85 c9                test   %rcx,%rcx
     3:   7e 20                   jle    25 <set_row+0x25>
     5:   48 0f af d1             imul   %rcx,%rdx
     9:   48 8d 14 d7             lea    (%rdi,%rdx,8),%rdx
     d:   b8 00 00 00 00          mov    $0x0,%eax
    12:   f2 0f 10 04 c6          movsd  (%rsi,%rax,8),%xmm0
    17:   f2 0f 11 04 c2          movsd  %xmm0,(%rdx,%rax,8)
    1c:   48 83 c0 01             add    $0x1,%rax
    20:   48 39 c1                cmp    %rax,%rcx
    23:   75 ed                   jne    12 <set_row+0x12>
    25:   f3 c3                   repz retq
  
  ```

  `gcc -O2` version: use ```xor %eax,%eax ``` instead of ```mov $0x0,%eax```

  `gcc -O3` version: (about 4-times longer code, I can't understand)

- **Reduction in Strength**

  - Replace costly operation with simpler one (Utility machine dependent)

  Examples:

  Shift, add instead of multiply, divide ```16*x```=>```x<<4```. Compilers will do this. 

  Recognize sequence products

  ```c
  for (i = 0; i < n; i++) {
    int ni = n*i;
    for (j = 0; j < n; j++)
      a[ni + j] = b[j];
  }
  ```

  ```c
  int ni = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      a[ni + j] = b[j];
    ni += n;
  }
  ```

- **Share Common Subexpressions**

  Reuse Expressions. Example:

  Four multiplications

  ```c
  /* Sum neighbors of i,j */
  up =    val[(i-1)*n + j  ];
  down =  val[(i+1)*n + j  ];
  left =  val[i*n     + j-1];
  right = val[i*n     + j+1];
  sum = up + down + left + right;
  ```

  One multiplication

  ```c
  long inj = i*n + j;
  up =    val[inj - n];
  down =  val[inj + n];
  left =  val[inj - 1];
  right = val[inj + 1];
  sum = up + down + left + right;
  ```

  GCC will do this with -O1

### Optimization Blockers

- **Limitations of Optimizing Compilers**
  - Operate under fundamental constraint: Must not cause any change in program behavior (Except Undefined Behaviours)
  - Behavior that may be obvious to the programmer can  be obfuscated by languages and coding styles: variable type ranges are bigger than what you use them for.
  - Most analysis is performed only within procedures: Whole-program analysis is too expensive. Let along different files. 
  - Most analysis is based only on static information: Runtime input cannot be predicted.
  - Conservative all the time!

- **Procedure calls**

  `strlen()`executed each loop. Can compiler move it out of loop? 

  ```c
  void lower(char *s)
  {
    size_t i;
    for (i = 0; i < strlen(s); i++)
      if (s[i] >= 'A' && s[i] <= 'Z')
        s[i] -= ('A' - 'a');
  }
  ```

  - Functions may have side-effects.
  - May not return same value for given arguments
  - Compilers treat them as blackboxes. 

  Use inline function. Do it your own. 

  Another example:

  ```c
  int counter = 0;
  int f(){
      return counter++;
  }
  
  int func1(){
      return f() + f() + f() + f();
  }
  int func2(){
      return 4 * f();
  }
  ```

- **Memory aliasing**

  func2 is faster due to less memory references. Can func1 be optimized to func2 ?

  ```c
  void func1(int *xp, int *yp)
  {
      *xp += *yp;
      *xp += *yp;
  }
  void func2(int *xp, int *yp)
  {
      *xp += 2 * *yp;
  }
  ```

  Nobody said `xp != yp` 

  - **Aliasing**: Two different memory references specify single location

    - Easy to have happen in C: Allow address arithmetic, direct access storage structures 

    - Get in habit of introducing local variables

      Accumulating within loops.

      **Your way of telling compiler not to check for aliasing**

  An implicit example:

  ```c
  /* Sum rows is of n X n matrix a
     and store in vector b  */
  void sum_rows1(double *a, double *b, long n) {
      long i, j;
      for (i = 0; i < n; i++) {
  	b[i] = 0;
  	for (j = 0; j < n; j++)
  	    b[i] += a[i*n + j]; // b[i] updated each loop, bad efficiency
      }
  }
  void sum_rows2(double *a, double *b, long n) {
      long i, j;
      for (i = 0; i < n; i++) {
  		double val = 0;
  		for (j = 0; j < n; j++)
  		    val += a[i*n + j]; // Less memory refencing here
      	b[i] = val;
      }
  }
  ```

  These are **not** same: each b[i] update affects program behavior. Compilers cannot optimize that. 

  ```c
  double A[9] = 
    { 0,   1,   2,
      4,   8,  16},
     32,  64, 128};
  double B[3] = A+3;
  sum_rows1(A, B, 3);
  ```


### Exploiting Instruction-Level Parallellism

- **Superscalar Processor**

  - Definition: A superscalar processor can issue and execute **multiple instructions in one cycle**. The instructions are retrieved from a sequential instruction stream and are usually scheduled dynamically.

- **Piplined Functional Units**

  - Divide computation into stages

  - Pass partial computations from stage to stage

  - Stage i can start on new computation once values passed to i+1

    Instructions take >1 cycle, but can be pipelined.

    ***Instruction  Latency  Cycles/Issue***

    **Load / Store  4  1** //need 1 cycle to issue instruction, and it will last for 4 cycles to complete

    **Integer Multiply  3  1**

    **Integer/Long Divide  3-30  3-30**

    **Single/Double FP Multiply  5  1**

    **Single/Double FP Add  3  1**

    **Single/Double FP Divide  3-15  3-15**

  Example: complete 3 multiplications in 7 cycles, even though each requires 3 cycles

  ```c
  long mult_eg(long a, long b, long c) {
      long p1 = a*b;
      long p2 = a*c;
      long p3 = p1 * p2;
      return p3;
  }
  ```

  ![1552264003979](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552264003979.png)

  |         | **Time** |          |          |          |            |            |            |
  | ------- | -------- | -------- | -------- | -------- | :--------- | ---------- | ---------- |
  |         | 1        | 2        | 3        | 4        | 5          | 6          | 7          |
  | Stage 1 | **a\*b** | **a\*c** |          |          | **p1\*p2** |            |            |
  | Stage 2 |          | **a\*b** | **a\*c** |          |            | **p1\*p2** |            |
  | Stage 3 |          |          | **a\*b** | **a\*c** |            |            | **p1\*p2** |

  **Visualizing Operations**

  ```assembly
  .L519:		# Loop:
  	imull	(%rax,%rdx,4), %ecx	# t = t * d[i]
  	addq	$1, %rdx	# i++
  	cmpq	%rdx, %rbp	# Compare length:i
  	jg	.L519	# If >, goto Loop
  ```

  ![1552267850694](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267850694.png)![1552267916805](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267916805.png)

  3 Iterations combined:(Resource Limited)

  ![1552267977402](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267977402.png)![1552268299944](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268299944.png)

  Find & Eliminate **critical path**!

- **Loop enrolling**

  ```c
  for (i = 0; i < limit; i+=2) {
  	x = (x OP d[i]) OP d[i+1];
  }
  ```

  ![1552268324558](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268324558.png)

  Performance increased.

  Can this be used in multiplication? Why not?

- **Reassociation**

  ```c
  #define OP *
  x = (x OP d[i]) OP d[i+1];	
  x = x OP (d[i] OP d[i+1]);
  ```

  Data dependency broke, parallelism enhanced.

  ![1552268751056](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268751056.png)

- **Seperate accumulators**

  Two independent “streams” of operations, parallelism enhanced.

  ```c
  for (i = 0; i < limit; i+=2) {
  	acc0 = acc0 OP data[i];
      acc1 = acc1 OP data[i+1];
  }
  ```

- **Register spliting**

  No enough registers, accumulators stored in stack and frequeny memory referencing.

- **Use vector instructions**

  ![1552265311980](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265311980.png)

### Conditionals

- **Challenge**

  Instruction Control Unit must work well ahead of Execution Unit to generate enough operations to keep EU busy

  When encounters conditional branch, cannot reliably determine where to continue fetching

- **Branch Prediction**

  **Guess** which way branch will go
  **Begin** executing instructions at predicted position, but don’t actually modify register or memory data

- **Misprediction**

  - Invalidate fetched instructions
  - Reload correct instructions (reload pipeline)
  - Cost multiple clock cycles(44 cycles on Intel Core i7). Can be major performance limiter

- **Don't Care Too Much?**

  - `for(i = 0; i < 100; i++)` Only the last prediction is wrong

  - Write code suitable for implementation with **Conditional Moves**(calculate both results before, and return the right one), "functional" style

    - Only 50% prediction rate, CPE 14.50

      ```c
      /* Rearrange two vectors so that for each i, b[i] >= a[i] */
      void minmax1(int a[], int b[], int n) {
      	int i;
      	for (i = 0; i < n; i++) {
      		if (a[i] > b[i]) {
      			int t = a[i];
      			a[i] = b[i];
      			b[i] = t;
      		}
      	}
      }
      ```

    - Conditional moves used, CPE 5.0

      ```c
      /* Rearrange two vectors so that for each i, b[i] >= a[i] */
      void minmax2(int a[], int b[], int n) {
      	int i;
      	for (i = 0; i < n; i++) {
      		int min = a[i] < b[i] ? a[i] : b[i];
      		int max = a[i] < b[i] ? b[i] : a[i];
      		a[i] = min;
      		b[i] = max;
      	}
      }
      ```

### Profiling

- **Tools**

  - Observation: Generate assembly code
  - Measurement: cycle counter, Unix tool `gprof`

- Example

  ![1552265021045](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265021045.png)

  ![1552265060158](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265060158.png)

  Single call(sort_words) use 87% of time

![1552265116179](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265116179.png)

Iter first: Use iterative function to insert elements into linked list. Causes code to slow down

Iter last: Iterative function, places new entry at end of list

Tend to place most common words at front of list

Big table: Increase number of hash buckets

Better hash: Use more sophisticated hash function

Linear lower: Move strlen out of loop

- **Amdahl’s Law**
  - Total time = (1-a)T + aT

    Component optimizing takes aT time.

    Improvement is factor of k, then:

    T_new = T_old[(1-a) + a/k]

    Speedup = T_old/T_new = 1/ [(1-a) + a/k]

    Maximum Achievable Speedup (k = Inf) = **1/(1-a)**

### Advice

- **Good compiler and flags**
- **Don’t do anything stupid**
  - Watch out for hidden algorithmic inefficiencies

  - Write compiler-friendly code

    Watch out for optimization blockers:  procedure calls & memory references

  - Look carefully at innermost loops (where most work is done)
- Tune code for machine

## Chap. 6 Memory

### Storage technologies and trends

- **RAM**

  ![1552790673400](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552790673400.png)

- **Nonvolatile**

  ROM, NAND, ...

- **Access Main Memory**

  Bus: a collection of parallel wires that carry address, data, and control signals. Shared by devices

  Memory bus

  Load operation `movl A,%eax`

  ![1552791090698](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791090698.png)

  ![1552791114325](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791114325.png)

  ![1552791153996](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791153996.png)

  Store operation `movl %eax,A`

  ![1552791196871](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791196871.png)

  ![1552791215775](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791215775.png)

  ![1552791238022](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791238022.png)

- **Hard Disk Drive**

  ![1552791458243](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791458243.png)

  Taccess  =  Tavg seek +  Tavg rotation + Tavg transfer 

  ~2500 times slower than DRAM

  Logical disk blocks

  I/O Bus

  ![1552791563046](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791563046.png)

  Read HDD sector

  ![1552791625187](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791625187.png)

  ![1552791641450](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791641450.png)

  ![1552791654456](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791654456.png)

- **Trend**

  DRAM and disk performance are lagging behind CPU performance.

  SRAM roughly keeping up.

  Gap between DRAM and disk and CPU performance widening.

### Locality

- In a program with good **temporal locality**, a memory location
  that is referenced once is likely to be referenced again multiple times in the near
  future. 

- In a program with good **spatial locality**, if a memory location is referenced
  once, then the program is likely to reference a nearby memory location in the near
  future.

- Programs with good locality run faster. Modern computer systems are designed to exploit locality.

- Both **references to program data** and **instruction fetches** have locality

- Example: 

  ```c
  sum = 0;
  for (i = 0; i < n; i++)
  	sum += a[i];
  return sum;
  ```

  Array a has good spatial locality(stride-1 reference pattern)

  Accumulator sum has good temporal locality(refered in each loop)

  Instruction: The for loop executed in sequential memory order(spatial), and executed multiple times(temporal).

### Memory Hierarchy

- Fundemental hardware and software properties complement each other.
- Storage devices get slower, bigger, and cheaper going from top to bottom

- **An example**

  ![1552792405981](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552792405981.png)

### Caches

- **Cache**:  a small, fast storage device that acts as a staging area for the data objects stored in a larger, slower device

- ![1552793025405](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552793025405.png)

- **Cache Hits**

- **Cache Misses**

  Fetch a block from lower level. May *replace* an existing block (require a good replacement policy)

  - **Kinds**
  - *Compulsary miss (cold miss)* Won't occur after warmed up. 
  - *Conflict miss* Cache is enough, but different blocks mapped to a same cache block, so keep missing.
  - *Capacity miss* Working set exceeded cache capacity. Cache too small. 

- Example: ubiquity of caches

  ![1552793944688](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552793944688.png)

- **Conclusion**

  - Caching works, because of locality
  - Maintaining locality is becoming more important as the memory gaps widened.

### Cache Memory in brief

- **Cache between CPU and DRAM**
  - L1, L2, L3 cache. SRAM
  - Miss rate: L1 3-10% , L2 <1%
  - Hit time: L1 one CPU cycle, L2 3-8 cycles
  - Miss penalty: 25-100 cycles DRAM

- **Write Cache-friendly Code**

  ```c
  int sumarrayrows(int a[M][N])
  {
      int i, j, sum = 0;
  
      for (i = 0; i < M; i++)
          for (j = 0; j < N; j++)
              sum += a[i][j];
      return sum;
  } // ~1/4 miss
  int sumarraycols(int a[M][N])
  {
      int i, j, sum = 0;
  
      for (j = 0; j < N; j++)
          for (i = 0; i < M; i++)
              sum += a[i][j];
      return sum;
  } // All miss
  ```

### The Memory Mountain

Two-dimensional function of read throughput versus temporal and spatial locality

```c
/* The test function */
void test(int elems, int stride) {
    int i, result = 0; 
    volatile int sink; 

    for (i = 0; i < elems; i += stride)
	result += data[i];
    sink = result; /* So compiler doesn't optimize away the loop */
}
/* Run test(elems, stride) and return read throughput (MB/s) */
double run(int size, int stride, double Mhz)
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     /* warm up the cache */
    cycles = fcyc2(test, elems, stride, 0);  /* call test(elems,stride) */
    return (size / stride) / (cycles / Mhz); /* convert cycles to MB/s */
}
```

Stride: spatial locality

Size: temporal locality

![1552795868102](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552795868102.png)

Ridges of temporal locality

![1552796089433](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552796089433.png)

A slope of spatial locality

![1552796118666](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552796118666.png)

### Example: Matrix-Matrix Multiplication

- Rearrange loops to increase spatial locality
- Use blocking to increase temporal locality

![1552810647449](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552810647449.png)

![1552810674234](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552810674234.png)

On my laptop: 

kji 9051ms

ijk 4909ms, 1832ms with `clang++ -O3`

ikj 3320ms, 406ms with `g++ -O3`

bijk 3088ms, 744ms with `g++ -O3`

Intel MKL 1 Core 56.25ms

## Others

- **Other Aspects and Advice**
  - Find out what is slow (Bad function, huge amount I/O, nested loops,  repeatous work, ...)
  - Better algorithm and data structure
  - Better interpreter (PyPy, ...)
  - Faster language (Python modules rewritten in C/C++)
  - Parallel, multithreading/multiprocessing
  - GPU instead of CPU
  - Use library (BLAS, MKL, ...), Never use your own implementation
  - ...