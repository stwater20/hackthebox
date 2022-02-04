struct packet
{
	int size;
	char buf[80000];
};

struct smb_info
{
	char userid[2];
	char treeid[2];
	char fid[2];
	char processid[2];
	char multiid[2];
	char callid;
};

struct versions
{
char name[100];
unsigned int start,end,step;
};

extern int hextoint(const char *value);
extern struct smb_info UniversalMethodRESPONSEFinal(struct smb_info current);
extern struct packet UniversalMethodFinal(struct smb_info info,struct packet stub,char opnum);
extern struct smb_info UniversalMethodRESPONSE(struct smb_info current);
extern struct packet UniversalMethod(struct smb_info info,struct packet stub,char opnum);
extern struct smb_info BINDRequestRESPONSE2nd(struct smb_info current,struct packet b);
extern struct packet BINDRequest2nd(struct smb_info info,char uid[100],int ver);
extern struct smb_info NTCreateAndXRequestRESPONSE2nd(struct smb_info current,struct packet b);
extern struct packet NTCreateAndXRequest2nd(struct smb_info info,char endpoint[100]);
extern struct smb_info TreeConnectAndXRequestRESPONSE2nd(struct smb_info current,struct packet b);
extern struct packet TreeConnectAndXRequest2nd(struct smb_info info);
extern struct smb_info SessionSetupAndXRequestRESPONSE2ndc(struct smb_info current,struct packet b);
extern struct packet SessionSetupAndXRequest2ndc(struct smb_info info);
extern struct smb_info SessionSetupAndXRequestRESPONSE2ndb(struct smb_info current,struct packet b);
extern struct packet SessionSetupAndXRequest2ndb(struct smb_info info);
extern struct smb_info SessionSetupAndXRequestRESPONSE2nd(struct smb_info current,struct packet b);
extern struct packet SessionSetupAndXRequest2nd(struct smb_info info);
extern struct smb_info NegotiateProtocolRequestRESPONSE2nd(struct smb_info current);
extern struct packet NegotiateProtocolRequest2nd(struct smb_info info);



