/* Copyright (C) 2006, 2007 The Written Word, Inc.  All rights reserved.
 * Author: Simon Josefsson
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 *   Redistributions of source code must retain the above
 *   copyright notice, this list of conditions and the
 *   following disclaimer.
 *
 *   Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials
 *   provided with the distribution.
 *
 *   Neither the name of the copyright holder nor the names
 *   of any other contributors may be used to endorse or
 *   promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 */

#include "openssl.h"

void _libssh2_rsa_new(libssh2_rsa_ctx **rsa,
		      const unsigned char *edata,
		      unsigned long elen,
		      const unsigned char *ndata,
		      unsigned long nlen)
{
	*rsa = RSA_new();
	(*rsa)->e = BN_new();
	BN_bin2bn(edata, elen, (*rsa)->e);
	(*rsa)->n = BN_new();
	BN_bin2bn(ndata, nlen, (*rsa)->n);
}

int _libssh2_rsa_sha1_verify(libssh2_rsa_ctx *rsactx,
			     const unsigned char *sig,
			     unsigned long sig_len,
			     const unsigned char *m,
			     unsigned long m_len)
{
	unsigned char hash[SHA_DIGEST_LENGTH];
	int ret;

	SHA1(m, m_len, hash);
	ret = RSA_verify(NID_sha1, hash, SHA_DIGEST_LENGTH,
			 (unsigned char *)sig, sig_len, rsactx);
	return (ret == 1) ? 0 : -1;
}
