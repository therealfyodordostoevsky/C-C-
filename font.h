unsigned char font[][22] = {
	{0xff}, // space
	{0x0f, 0x05, 0x1f, 0x85, 0x0f, 0xb5, 0x1f, 0xc6, 0xd5, 0xc4, 0xb5, 0xff}, // excla
	{0x0f, 0x03, 0x1f, 0x33, 0x0f, 0x07, 0x1f, 0x37, 0xff}, // quote
	{0x0f, 0xa0, 0x1f, 0x25, 0x0f, 0xa5, 0x1f, 0x2a, 0x0f, 0x41, 0x1f, 0x49, 0x0f, 0x81, 0x1f, 0x89, 0xff}, // number
	{0x0f, 0x19, 0x1f, 0x13, 0x31, 0x41, 0x63, 0x67, 0x89, 0x99, 0xb7, 0xb0, 0x0f, 0x05, 0x1f, 0xd5, 0xff}, // dollar
	{0x1f, 0x0a, 0x01, 0x41, 0x45, 0x05, 0x0f, 0x76, 0x1f, 0x7a, 0xba, 0xb6, 0x76, 0xff}, // percent
	{0x0f, 0xca, 0x1f, 0xa8, 0x65, 0x44, 0x33, 0x23, 0x04, 0x05, 0x16, 0x26, 0x45, 0x54, 0x62, 0x81, 0xa2, 0xb3, 0xc5, 0xb7, 0x8a, 0xff}, // amper
	{0x0f, 0x07, 0x1f, 0x23, 0xff}, // accr
	{0x0f, 0x06, 0x1f, 0x24, 0xa4, 0xd7, 0xff}, // lparn
	{0x0f, 0x04, 0x1f, 0x26, 0xa6, 0xd3, 0xff}, // rparn
	{0x0f, 0x61, 0x1f, 0x6a, 0x0f, 0x33, 0x1f, 0xa8, 0x0f, 0x37, 0x1f, 0xa2, 0xff}, // aster
	{0x0f, 0x61, 0x1f, 0x6a, 0x0f, 0x25, 0x1f, 0xb5, 0xff}, // plus
	{0x0f, 0xc5, 0x1f, 0xc6, 0xe4, 0xc5, 0xff}, // comma
	{0x0f, 0x61, 0x1f, 0x6a, 0xff}, // minus
	{0x0f, 0xb4, 0x1f, 0xb5, 0xc5, 0xc4, 0xb4, 0xff}, // period
	{0x1f, 0x0a, 0x0f, 0x1f, 0x19, 0xff}, // sla
	{0x0f, 0x2a, 0x1f, 0x08, 0x02, 0x20, 0xa0, 0xc2, 0xc8, 0xaa, 0x2a, 0xff}, // c0
	{0x0f, 0x24, 0x1f, 0x05, 0xc5, 0x0f, 0xc3, 0x1f, 0xc8, 0xff}, // c1
	{0x0f, 0x20, 0x1f, 0x02, 0x08, 0x2a, 0x4a, 0x68, 0x62, 0x80, 0xc0, 0xcb, 0xff}, // c2
	{0x0f, 0x00, 0x1f, 0x0a, 0x54, 0x58, 0x7a, 0xaa, 0xc8, 0xc2, 0x0f, 0xa0, 0x1f, 0xc2, 0xff}, // c3
	{0x0f, 0xc7, 0x1f, 0x07, 0x80, 0x8b, 0xff}, // c4
	{0x0f, 0x0a, 0x1f, 0x00, 0x50, 0x58, 0x7a, 0xaa, 0xc8, 0xc2, 0x0f, 0xa0, 0x1f, 0xc2, 0xff}, // c5
	{0x0f, 0x2a, 0x1f, 0x08, 0x02, 0x20, 0xa0, 0xc2, 0xc8, 0xaa, 0x7a, 0x58, 0x52, 0x70, 0xff}, // c6
	{0x0f, 0x00, 0x1f, 0x0a, 0xd1, 0xff}, // c7
	{0x0f, 0x62, 0x1f, 0x40, 0x20, 0x02, 0x08, 0x2a, 0x4a, 0x68, 0x62, 0x80, 0xa0, 0xc2, 0xc8, 0xaa, 0x8a, 0x68, 0xff}, // c8
	{0x0f, 0xa0, 0x1f, 0xc2, 0xc8, 0xaa, 0x2a, 0x08, 0x02, 0x20, 0x50, 0x72, 0x78, 0x5a, 0xff}, // c9
	{0x0f, 0xb4, 0x1f, 0xb5, 0xc5, 0xc4, 0xb4, 0x0f, 0x54, 0x1f, 0x55, 0x65, 0x64, 0x54, 0xff}, // colon
	{0x0f, 0xc5, 0x1f, 0xc6, 0xe4, 0xc5, 0x0f, 0x55, 0x1f, 0x56, 0x66, 0x64, 0x54, 0xff}, // semcln
	{0x0f, 0x29, 0x1f, 0x61, 0xa9, 0xff}, // less
	{0x0f, 0x41, 0x1f, 0x4a, 0x0f, 0x81, 0x1f, 0x8a, 0xff}, // equal
	{0x0f, 0x21, 0x1f, 0x69, 0xa1, 0xff}, // great
	{0x0f, 0x41, 0x1f, 0x12, 0x05, 0x18, 0x4a, 0x85, 0xc5, 0xff}, // quest
	{0x1f, 0x00, 0x0a, 0xca, 0xc0, 0x0f, 0x2a, 0x1f, 0x23, 0xa3, 0xab, 0xff}, // at
	{0x1f, 0x05, 0xdb, 0x0f, 0x73, 0x1f, 0x78, 0xff}, // ca
	{0x0f, 0x60, 0x1f, 0x68, 0x8a, 0xaa, 0xc8, 0xc0, 0x00, 0x08, 0x2a, 0x4a, 0x68, 0xff}, // cb
	{0x0f, 0xaa, 0x1f, 0xc8, 0xc2, 0xa0, 0x20, 0x02, 0x08, 0x3b, 0xff}, // cc
	{0x1f, 0x00, 0x08, 0x2a, 0xaa, 0xc8, 0xc0, 0xff}, // cd
	{0x0f, 0xca, 0x1f, 0xc0, 0x00, 0x0a, 0x0f, 0x67, 0x1f, 0x60, 0xff}, // ce
	{0x1f, 0x00, 0x0a, 0x0f, 0x67, 0x1f, 0x60, 0xff}, // cf
	{0x0f, 0x65, 0x1f, 0x6a, 0xda, 0x0f, 0xaa, 0x1f, 0xc8, 0xc2, 0xa0, 0x20, 0x02, 0x08, 0x3b, 0xff}, // cg
	{0x0f, 0x00, 0x1f, 0xd0, 0x0f, 0x61, 0x1f, 0x6a, 0x0f, 0x0a, 0x1f, 0xda, 0xff}, // ch
	{0x0f, 0xc3, 0x1f, 0xc8, 0x0f, 0xb5, 0x1f, 0x05, 0x0f, 0x03, 0x1f, 0x08, 0xff}, // ci
	{0x0f, 0xa0, 0x1f, 0xc2, 0xc6, 0xa8, 0x08, 0x0f, 0x06, 0x1f, 0x0b, 0xff}, // cj
	{0x0f, 0x00, 0x1f, 0xd0, 0x0f, 0x0a, 0x1f, 0x80, 0x0f, 0xca, 0x1f, 0x54, 0xff}, // ck
	{0x0f, 0x00, 0x1f, 0xc0, 0xca, 0xff}, // cl
	{0x1f, 0x00, 0x75, 0x0a, 0xda, 0xff}, // cm
	{0x0f, 0x0a, 0x1f, 0xca, 0x00, 0xd0, 0xff}, // cn
	{0x0f, 0x08, 0x1f, 0x27, 0x48, 0x2a, 0x08, 0x02, 0x20, 0xa0, 0xc2, 0xc8, 0xaa, 0x2a, 0xff}, // co
	{0x1f, 0x00, 0x08, 0x2a, 0x4a, 0x68, 0x60, 0xff}, // cp
	{0x0f, 0xc2, 0x1f, 0xa0, 0x20, 0x02, 0x08, 0x2a, 0xaa, 0xc8, 0xc2, 0x0f, 0x97, 0x1f, 0xdb, 0xff}, // cq
	{0x1f, 0x00, 0x08, 0x2a, 0x4a, 0x68, 0x60, 0x0f, 0xca, 0x1f, 0x65, 0xff}, // cr
	{0x0f, 0xa0, 0x1f, 0xc2, 0xc8, 0xaa, 0x8a, 0x68, 0x62, 0x40, 0x20, 0x02, 0x08, 0x3b, 0xff}, // cs
	{0x0f, 0x00, 0x1f, 0x0b, 0x0f, 0xc5, 0x1f, 0x05, 0xff}, // ct
	{0x0f, 0x00, 0x1f, 0xa0, 0xc2, 0xc8, 0xaa, 0x0f, 0x0a, 0x1f, 0xba, 0xff}, // cu
	{0x0f, 0x00, 0x1f, 0xc5, 0x0f, 0x0a, 0x1f, 0xc5, 0xff}, // cv
	{0x0f, 0x00, 0x1f, 0xc2, 0x05, 0x0f, 0x0a, 0x1f, 0xc8, 0x05, 0xff}, // cw
	{0x1f, 0x65, 0x0f, 0x0a, 0x1f, 0x65, 0x0f, 0x00, 0x1f, 0xdb, 0xff}, // cx
	{0x0f, 0x00, 0x1f, 0x85, 0x0f, 0x0a, 0x1f, 0x85, 0xd5, 0xff}, // cy
	{0x0f, 0x00, 0x1f, 0x0a, 0xc0, 0xcb, 0xff}, // cz
	{0x0f, 0x08, 0x1f, 0x05, 0xc5, 0xc9, 0xff}, // lbk
	{0x0f, 0x00, 0x1f, 0xdb, 0xff}, // bsla
	{0x0f, 0x02, 0x1f, 0x05, 0xc5, 0xc1, 0xff}, // rbk
	{0x0f, 0x12, 0x1f, 0x05, 0x19, 0xff}, // cmflx
	{0x0f, 0xd0, 0x1f, 0xdd, 0xff}, // under
	{0x0f, 0x03, 0x1f, 0x27, 0xff}, // accl
	{0x0f, 0x51, 0x1f, 0x34, 0x37, 0x5a, 0xda, 0x0f, 0x8a, 0x1f, 0x67, 0x64, 0x81, 0xa1, 0xc4, 0xc7, 0xaa, 0xff}, // la
	{0x0f, 0x10, 0x1f, 0xd1, 0x0f, 0x61, 0x1f, 0x44, 0x47, 0x6a, 0xaa, 0xc7, 0xc4, 0xa1, 0xff}, // lb
	{0x0f, 0xaa, 0x1f, 0xc7, 0xc4, 0xa1, 0x61, 0x44, 0x47, 0x7b, 0xff}, // lc
	{0x0f, 0x0a, 0x1f, 0xda, 0x0f, 0x6a, 0x1f, 0x47, 0x44, 0x61, 0xa1, 0xc4, 0xc7, 0xaa, 0xff}, // ld
	{0x0f, 0xba, 0x1f, 0xc7, 0xc4, 0xa1, 0x61, 0x44, 0x47, 0x6a, 0x8a, 0x81, 0xff}, // le
	{0x0f, 0xc4, 0x1f, 0x24, 0x06, 0x0a, 0x0f, 0x52, 0x1f, 0x58, 0xff}, // lf
	{0x0f, 0xd1, 0x1f, 0xf4, 0xf7, 0xca, 0x6a, 0x47, 0x44, 0x61, 0x91, 0xb4, 0xb7, 0x9a, 0xff}, // lg
	{0x0f, 0x01, 0x1f, 0xd1, 0x0f, 0x71, 0x1f, 0x54, 0x57, 0x7a, 0xda, 0xff}, // lh
	{0x0f, 0x24, 0x1f, 0x26, 0x46, 0x44, 0x24, 0x0f, 0x62, 0x1f, 0x65, 0xc5, 0x0f, 0xc2, 0x1f, 0xc8, 0xff}, // li
	{0x0f, 0xc1, 0x1f, 0xe3, 0xe5, 0xc7, 0x57, 0x53, 0x0f, 0x24, 0x1f, 0x26, 0x46, 0x44, 0x24, 0xff}, // lj
	{0x0f, 0x21, 0x1f, 0xd1, 0x0f, 0x91, 0x1f, 0x4a, 0x0f, 0x73, 0x1f, 0xdb, 0xff}, // lk
	{0x0f, 0xc3, 0x1f, 0xc9, 0x0f, 0xc6, 0x1f, 0x16, 0x14, 0xff}, // ll
	{0x1f, 0x40, 0x0f, 0x70, 0x1f, 0x51, 0x53, 0x75, 0x56, 0x59, 0x7a, 0xda, 0x0f, 0x75, 0x1f, 0xd5, 0xff}, // lm
	{0x0f, 0x51, 0x1f, 0xd1, 0x0f, 0x71, 0x1f, 0x55, 0x57, 0x7a, 0xda, 0xff}, // ln
	{0x0f, 0xa1, 0x1f, 0x71, 0x54, 0x57, 0x7a, 0xaa, 0xc7, 0xc4, 0xa1, 0xff}, // lo
	{0x0f, 0xf1, 0x1f, 0x41, 0x0f, 0x71, 0x1f, 0x54, 0x56, 0x7a, 0xaa, 0xc6, 0xc4, 0xa1, 0xff}, // lp
	{0x0f, 0x5a, 0x1f, 0xfa, 0xfc, 0x0f, 0x7a, 0x1f, 0x57, 0x54, 0x71, 0xa1, 0xc4, 0xc7, 0xaa, 0xff}, // lq
	{0x0f, 0xc3, 0x1f, 0x63, 0x0f, 0x51, 0x1f, 0x63, 0x55, 0x57, 0x69, 0xff}, // lr
	{0x0f, 0xa1, 0x1f, 0xc3, 0xc7, 0xb9, 0x89, 0x77, 0x63, 0x43, 0x34, 0x38, 0x59, 0xff}, // ls
	{0x0f, 0x31, 0x1f, 0x39, 0x0f, 0x04, 0x1f, 0xa4, 0xc5, 0xc7, 0xb9, 0xff}, // lt
	{0x0f, 0x31, 0x1f, 0xa1, 0xc3, 0xc6, 0xa8, 0x28, 0x0f, 0xca, 0x1f, 0xa8, 0xff}, // lu
	{0x0f, 0x31, 0x1f, 0xc5, 0x39, 0xff}, // lv
	{0x0f, 0x30, 0x1f, 0xc3, 0x66, 0xc9, 0x3c, 0xff}, // lw
	{0x0f, 0x31, 0x1f, 0xdb, 0x0f, 0x39, 0x1f, 0xd0, 0xff}, // lx
	{0x0f, 0x31, 0x1f, 0xc5, 0x0f, 0x39, 0x1f, 0xe4, 0xe1, 0xff}, // ly
	{0x0f, 0x32, 0x1f, 0x38, 0xc1, 0xc9, 0xff}, // lz
	{0x0f, 0x08, 0x1f, 0x15, 0x55, 0x63, 0x75, 0xb5, 0xd9, 0xff}, // lbr
	{0x0f, 0x05, 0x1f, 0xd5, 0xff}, // or
	{0x0f, 0x02, 0x1f, 0x15, 0x55, 0x67, 0x75, 0xb5, 0xd1, 0xff}, // rbr
	{0x0f, 0x08, 0x1f, 0x37, 0x03, 0x31, 0xff}, // tild
};