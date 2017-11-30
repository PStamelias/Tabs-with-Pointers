/*
Name:Prokopios Stamelias
AM 1115201400190
*/
#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession*     InfoSessionPtr;

InfoSessionPtr SessionNew(const char *);
void SessionNewTab(InfoSessionPtr* , char*);
void SessionAddressShow(InfoSessionPtr );
void SessionTabNext(InfoSessionPtr* );
void SessionTabPrev(InfoSessionPtr* );
void SessionNewOpeningAddress(InfoSessionPtr*  , char*  );
void SessionShowOpeningAddress(InfoSessionPtr );
void SessionSiteNext(InfoSessionPtr*  );
void SessionSitePrev(InfoSessionPtr*  );
void SessionTabMoveLeft(InfoSessionPtr*  );
void SessionTabMoveRight(InfoSessionPtr*  );
void SessionTabClose(InfoSessionPtr*  );
void SessionClose(InfoSessionPtr*  );
void SessionNewAddress(InfoSessionPtr* ,char* );
void SessionOpenNewTab(InfoSessionPtr* );

#endif
