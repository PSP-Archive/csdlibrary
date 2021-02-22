/******************************************************************************
 *                                                                            *
 *      stype.h                                                               *
 *                                                                            *
 *      �����񏈗��֐�                                                        *
 *                                                                            *
 ******************************************************************************/

#ifndef _STYPE_H
#define _STYPE_H

#define __need_size_t
#include <stddef.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		�������胂�[�h�imischar mode, sischar mode�j
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

// �_����
#define ISL_OR			0x00000000			// �S����̘_���a
#define ISL_AND			0x10000000			// �S����̘_����
#define ISL_ORNOT		0x20000000			// �S����̘_���a�̔ے�
#define ISL_ANDNOT		0x30000000			// �S����̘_���ς̔ے�

// ����
#define ISJ_SPACE		0x00000001			// �Ԋu����
#define ISJ_DIGIT		0x00000002			// ����
#define ISJ_UPPER		0x00000004			// �p�啶��
#define ISJ_LOWER		0x00000008			// �p������
#define ISJ_XDIGIT		0x00000010			// 16�i�\�L����
#define ISJ_CNTRL		0x00000020			// ���䕶��
#define ISJ_PUNCT		0x00000040			// ��؂蕶��
#define ISJ_BLANK		0x00000080			// �󔒕���
#define ISJ_KMOJI		0x00000100			// ��Ǔ_�ȊO�̔��p�J�i����
#define ISJ_KPUN		0x00000200			// ���p�J�i�����̋�Ǔ_
#define ISJ_JJIS		0x00000400			// JIS�R�[�h
#define ISJ_JSJIS		0x00000800			// �V�t�gJIS�R�[�h
#define ISJ_JKUTEN		0x00001000			// ��_�R�[�h
#define ISJ_JL0			0x00002000			// �V�t�gJIS�̊����ȊO�̕���
#define ISJ_JL1			0x00004000			// �V�t�gJIS��ꐅ��
#define ISJ_JL2			0x00008000			// �V�t�gJIS��񐅏�
#define ISJ_JALPHA		0x00010000			// �V�t�gJIS�̉p����
#define ISJ_JUPPER		0x00020000			// �V�t�gJIS�̉p�啶��
#define ISJ_JLOWER		0x00040000			// �V�t�gJIS�̉p������
#define ISJ_JDIGIT		0x00080000			// �V�t�gJIS�̐���
#define ISJ_JKANA		0x00100000			// �V�t�gJIS�̃J�^�J�i
#define ISJ_JHIRA		0x00200000			// �V�t�gJIS�̂Ђ炪��
#define ISJ_JKIGOU		0x00400000			// �V�t�gJIS�̋L��
#define ISJ_JSPACE		0x00800000			// �V�t�gJIS�̃X�y�[�X

#define ISJ_ALPHA		ISJ_UPPER | ISJ_LOWER	// �p����
#define ISJ_ALNUM		ISJ_DIGIT | ISJ_ALPHA	// �p�����Ɛ���
#define ISJ_GRAPH		ISJ_ALNUM | ISJ_PUNCT	// �󔒈ȊO�̕\���\����
#define ISJ_PRINT		ISJ_GRAPH | ISJ_BLANK	// �\���\����
#define ISJ_ASCII		ISJ_PRINT | ISJ_CNTRL	// ASCII����
#define ISJ_KANA		ISJ_KMOJI | ISJ_KPUN	// ���p�̃J�i����
#define ISJ_ALKANA		ISJ_ALPHA | ISJ_KMOJI	// �p�����ƃJ�i����
#define ISJ_PNKANA		ISJ_PUNCT | ISJ_KPUN	// �p���̋�Ǔ_�ƃJ�i�����̋�Ǔ_
#define ISJ_ALNMKANA	ISJ_ALNUM | ISJ_KMOJI	// �p�����Ɛ����ƃJ�i����
#define ISJ_PRKANA		ISJ_PRINT | ISJ_KANA	// �\���\�����ƃJ�i����
#define ISJ_GRKANA		ISJ_GRAPH | ISJ_KANA	// �󔒈ȊO�̕\���\�����ƃJ�i����
#define ISJ_PRKASJ		ISJ_PRKANA | ISJ_JSJIS	// �\���\�����ƃJ�i�����ƃV�t�gJIS

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		��������ȊO�Ώہimischar except, sischar except�j
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#define ISE_NONE		0x00000000			// �Ȃ�
#define ISE_SPACE		0x00000001			// �Ԋu����
#define ISE_DIGIT		0x00000002			// ����
#define ISE_UPPER		0x00000004			// �p�啶��
#define ISE_LOWER		0x00000008			// �p������
#define ISE_XDIGIT		0x00000010			// 16�i�\�L����
#define ISE_CNTRL		0x00000020			// ���䕶��
#define ISE_PUNCT		0x00000040			// ��؂蕶��
#define ISE_BLANK		0x00000080			// �󔒕���
#define ISE_KMOJI		0x00000100			// ��Ǔ_�ȊO�̔��p�J�i����
#define ISE_KPUN		0x00000200			// ���p�J�i�����̋�Ǔ_
#define ISE_JJIS		0x00000400			// JIS�R�[�h
#define ISE_JSJIS		0x00000800			// �V�t�gJIS�R�[�h
#define ISE_JKUTEN		0x00001000			// ��_�R�[�h
#define ISE_JL0			0x00002000			// �V�t�gJIS�̊����ȊO�̕���
#define ISE_JL1			0x00004000			// �V�t�gJIS��ꐅ��
#define ISE_JL2			0x00008000			// �V�t�gJIS��񐅏�
#define ISE_JALPHA		0x00010000			// �V�t�gJIS�̉p����
#define ISE_JUPPER		0x00020000			// �V�t�gJIS�̉p�啶��
#define ISE_JLOWER		0x00040000			// �V�t�gJIS�̉p������
#define ISE_JDIGIT		0x00080000			// �V�t�gJIS�̐���
#define ISE_JKANA		0x00100000			// �V�t�gJIS�̃J�^�J�i
#define ISE_JHIRA		0x00200000			// �V�t�gJIS�̂Ђ炪��
#define ISE_JKIGOU		0x00400000			// �V�t�gJIS�̋L��
#define ISE_JSPACE		0x00800000			// �V�t�gJIS�̃X�y�[�X
#define ISE_ALL			0x00ffffff			// �S��

#define ISE_ALPHA		ISE_UPPER | ISE_LOWER	// �p����
#define ISE_ALNUM		ISE_DIGIT | ISE_ALPHA	// �p�����Ɛ���
#define ISE_GRAPH		ISE_ALNUM | ISE_PUNCT	// �󔒈ȊO�̕\���\����
#define ISE_PRINT		ISE_GRAPH | ISE_BLANK	// �\���\����
#define ISE_ASCII		ISE_PRINT | ISE_CNTRL	// ASCII����
#define ISE_KANA		ISE_KMOJI | ISE_KPUN	// ���p�̃J�i����
#define ISE_ALKANA		ISE_ALPHA | ISE_KMOJI	// �p�����ƃJ�i����
#define ISE_PNKANA		ISE_PUNCT | ISE_KPUN	// �p���̋�Ǔ_�ƃJ�i�����̋�Ǔ_
#define ISE_ALNMKANA	ISE_ALNUM | ISE_KMOJI	// �p�����Ɛ����ƃJ�i����
#define ISE_PRKANA		ISE_PRINT | ISE_KANA	// �\���\�����ƃJ�i����
#define ISE_GRKANA		ISE_GRAPH | ISE_KANA	// �󔒈ȊO�̕\���\�����ƃJ�i����
#define ISE_PRKASJ		ISJ_PRKANA | ISJ_JSJIS	// �\���\�����ƃJ�i�����ƃV�t�gJIS

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ *
		�v���g�^�C�v�錾
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifdef __cplusplus
extern "C" {
#endif
void *mischar(const void *mem, size_t size, long mode, long except);
void *misrange(const void *mem, size_t size, unsigned long min, unsigned long max);
void *misxrange(const void *mem, size_t size, unsigned long min, unsigned long max);
int sischar(const char *str, long mode, long except);
int sisrange(const char *str, unsigned long min, unsigned long max);
int sisxrange(const char *str, unsigned long min, unsigned long max);
int ttostr(char *str, const char *mode, const void *value);
int strtot(const char *str, const char *mode, void *value);
void strltrim(char *str);
void strrtrim(char *str);
void strtrim(char *str);
void strleft(char *dest, const char *src, size_t len);
void strmid(char *dest, const char *src, int start, size_t len);
void strright(char *dest, const char *src, size_t len);
#ifdef __cplusplus
}
#endif

#endif
