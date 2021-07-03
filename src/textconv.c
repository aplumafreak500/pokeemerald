#include <stdlib.h>
#include "global.h"
#include "text.h"
#include "string_util.h"

char* pokeTextToCharN(char* dest, const u8* src, u32 limit) {
	char* ret = dest;
	u32 i;
	wchar_t w;
	wctomb(NULL, 0);
	for (i = 0; i < limit; i++) {
		w = 0xfffd;
		switch (*src) {
			default:
				break;
			case 0:
				w = ' ';
				break;
			case 1 ... 3:
				w = 0xc2 - (*src - 1);
				break;
			// ... TODO
			case 0x2d:
				w = '&';
				break;
			case 0x2e:
				w = '+';
				break;
			// ... TODO
			case 0x34:
				*ret = 'L';
				ret++;
				*ret = 'v';
				ret++;
				*ret = '.';
				ret++;
				src++;
				continue;
			case 0x35:
				w = '=';
				break;
			case 0x36:
				w = ';';
				break;
			// ... TODO
			case 0x51:
				w = 0xbf;
				break;
			case 0x52:
				w = 0xa1;
				break;
			case 0x53:
				*ret = 'P';
				ret++;
				*ret = 'K';
				ret++;
				src++;
				continue;
			case 0x54:
				*ret = 'M';
				ret++;
				*ret = 'N';
				ret++;
				src++;
				continue;
			case 0x55:
				*ret = 'P';
				ret++;
				*ret = 'O';
				ret++;
				src++;
				continue;
			case 0x56:
				*ret = 'K';
				ret++;
				*ret = 'E';
				ret++;
				src++;
				continue;
			case 0x57:
				*ret = 'B';
				ret++;
				*ret = 'L';
				ret++;
				src++;
				continue;
			case 0x58:
				*ret = 'O';
				ret++;
				*ret = 'C';
				ret++;
				src++;
				continue;
			case 0x59:
				*ret = 'K';
				ret++;
				src++;
				continue;
			// 0x5a TODO
			case 0x5b:
				w = '%';
				break;
			case 0x5c:
				w = '(';
				break;
			case 0x5d:
				w = ')';
				break;
			// ... TODO
			case 0x85:
				w = '<';
				break;
			case 0x86:
				w = '>';
				break;
			// ... TODO
			case 0xa1 ... 0xaa:
				w = '9' - (*src - 0xa1);
				break;
			case 0xab:
				w = '!';
				break;
			case 0xac:
				w = '?';
				break;
			case 0xad:
				w = '.';
				break;
			case 0xae:
				w = '-';
				break;
			// ... TODO
			case 0xb7:
				w = '$';
				break;
			case 0xb8:
				w = ',';
				break;
			case 0xb9:
				w = 0xd7;
				break;
			case 0xba:
				w = '/';
				break;
			case 0xbb ... 0xd4:
				w = 'Z' - (*src - 0xbb);
				break;
			case 0xd5 ... 0xee:
				w = 'z' - (*src - 0xd5);
				break;
			// ... TODO
			case 0xf0:
				w = ':';
				break;
			// ... TODO
			case 0xff:
				w = '\0';
				break;
		}
		ret += wctomb(ret, w);
		src++;
	}
	return ret;
}

char* pokeTextToChar(char* dest, const u8* src) {
	return pokeTextToCharN(dest, src, StringLength(src));
}

u8* charToPokeTextN(u8* dest, const char* src, u32 limit) {
	u8* ret = dest;
	u32 i;
	wchar_t w;
	u8 c;
	mbtowc(NULL, 0, 0);
	for (i = 0; i < limit; i++) {
		c = CHAR_QUESTION_MARK;
		src += mbtowc(&w, src, 4);
		switch (w) {
			default:
			case '?':
				break;
			case '\0':
				c = EOS;
				break;
			case ' ':
				c = CHAR_SPACE;
				break;
			case '!':
				c = CHAR_EXCL_MARK;
				break;
			
		}
		*ret = c;
		ret++;
		break;
	}
	return ret;
}

u8* charToPokeText(u8* dest, const char* src) {
	return charToPokeTextN(dest, src, strlen(src));
}
