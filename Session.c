/*
Name:Prokopios Stamelias
AM 1115201400190
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Session.h"

typedef struct TabNode *TabNodePtr;
typedef struct SiteNode *SiteNodePtr;

struct InfoSession {
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;
	TabNodePtr AuxTab;
	char* 	  OpeningAddress;
};

struct TabNode {	
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
};

struct SiteNode{
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};


InfoSessionPtr SessionNew(const char* OpeningAddress){
	InfoSessionPtr MySession=malloc(sizeof(struct InfoSession));
	TabNodePtr Tab=malloc(sizeof(struct TabNode ));
	SiteNodePtr Site=malloc(sizeof(struct SiteNode));
	MySession->FirstTab=Tab;
	MySession->CurrTab=Tab;
	MySession->LastTab=Tab;	
	MySession->AuxTab=NULL;
	Tab->FirstSite=Site;
	Tab->CurrSite=Site;
	Tab->NextTab=NULL;
	Tab->PrevTab=NULL;
	Site->UpTab=Tab;
	Site->NextSite=NULL;
	Site->PrevSite=NULL;
	MySession->OpeningAddress=malloc(sizeof(strlen(OpeningAddress))+1);
	strcpy(MySession->OpeningAddress,OpeningAddress);
	Site->Address=malloc(sizeof(strlen(MySession->OpeningAddress))+1);
	strcpy(Site->Address,MySession->OpeningAddress);
	return MySession;
}

void SessionNewTab(InfoSessionPtr* Session,char* Address){
	assert(*Session!=NULL);
	TabNodePtr Tab=malloc(sizeof(struct TabNode));
	SiteNodePtr Site=malloc(sizeof(struct SiteNode));
	Tab->NextTab=(*Session)->FirstTab;
	Tab->PrevTab=(*Session)->LastTab;
	(*Session)->LastTab->NextTab=Tab;
	(*Session)->LastTab=Tab;
	(*Session)->CurrTab=Tab;
	(*Session)->FirstTab->PrevTab=Tab;
	Tab->FirstSite=Site;
	Tab->CurrSite=Site;
	Site->UpTab=Tab;
	Site->NextSite=NULL;
	Site->PrevSite=NULL;
	Site->Address=malloc(sizeof(strlen(Address))+1);
	strcpy(Site->Address,Address);
	
}

void SessionAddressShow(InfoSessionPtr Session)
{
	assert(Session!=NULL);
	printf("%s\n",Session->CurrTab->CurrSite->Address);
}

void SessionTabNext(InfoSessionPtr*  Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab->NextTab==NULL)
		return ;
	(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
}

void SessionTabPrev(InfoSessionPtr* Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab->PrevTab==NULL)
		return ;	
	(*Session)->CurrTab=(*Session)->CurrTab->PrevTab;
}

void SessionNewOpeningAddress(InfoSessionPtr* Session, char* Address)
{
	assert(*Session!=NULL);
	(*Session)->OpeningAddress=(char* )realloc((*Session)->OpeningAddress,sizeof(strlen(Address)+1));
	strcpy((*Session)->OpeningAddress,Address);
	
}

void SessionShowOpeningAddress(InfoSessionPtr Session)
{
	assert(Session!=NULL);
	printf("%s\n",Session->OpeningAddress);
}

void SessionSiteNext(InfoSessionPtr*  Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab->CurrSite->NextSite==NULL)
		return ;
	(*Session)->CurrTab->CurrSite=(*Session)->CurrTab->CurrSite->NextSite;
}

void SessionSitePrev(InfoSessionPtr*  Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab->CurrSite->PrevSite==NULL)
		return ;
	(*Session)->CurrTab->CurrSite=(*Session)->CurrTab->CurrSite->PrevSite;
}

void SessionTabMoveLeft(InfoSessionPtr*  Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab==(*Session)->FirstTab)
		return ;
	 if((*Session)->CurrTab->PrevTab==(*Session)->FirstTab)
	{
		if((*Session)->CurrTab->NextTab==(*Session)->CurrTab->PrevTab)//it means that i have two Tabs 
		{	
			
			(*Session)->FirstTab=(*Session)->CurrTab;
			(*Session)->LastTab=(*Session)->CurrTab->NextTab;
			return ;
		}
		(*Session)->FirstTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->PrevTab=(*Session)->FirstTab->PrevTab;
		(*Session)->FirstTab->PrevTab=(*Session)->CurrTab;
		(*Session)->CurrTab->NextTab=(*Session)->FirstTab;
		(*Session)->LastTab->NextTab=(*Session)->CurrTab;
		(*Session)->FirstTab=(*Session)->CurrTab;
	}
	else if((*Session)->CurrTab==(*Session)->LastTab)
	{
		
		(*Session)->FirstTab->PrevTab=(*Session)->LastTab->PrevTab;
		(*Session)->CurrTab->PrevTab->PrevTab->NextTab=(*Session)->LastTab;
		(*Session)->CurrTab->PrevTab->PrevTab->NextTab=(*Session)->CurrTab;
		(*Session)->CurrTab->NextTab=(*Session)->CurrTab->PrevTab;
		(*Session)->LastTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab->PrevTab=(*Session)->CurrTab->PrevTab->PrevTab;
		(*Session)->LastTab->NextTab=(*Session)->FirstTab;
	}
	else
	{
		
		(*Session)->CurrTab->PrevTab->PrevTab->NextTab=(*Session)->CurrTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab->PrevTab=(*Session)->CurrTab->PrevTab->PrevTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab;
		
	}
}

void SessionTabMoveRight(InfoSessionPtr* Session)
{
	assert(*Session!=NULL);
	if((*Session)->CurrTab==(*Session)->LastTab)
		return ;
	if((*Session)->CurrTab->NextTab==(*Session)->LastTab)
	{
		
		if((*Session)->CurrTab->NextTab==((*Session)->CurrTab->PrevTab))
		{
			
			(*Session)->LastTab=(*Session)->CurrTab;
			(*Session)->FirstTab=(*Session)->CurrTab->NextTab;
			return ;
		}
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->LastTab;
		(*Session)->CurrTab->NextTab=(*Session)->FirstTab;
		(*Session)->FirstTab->PrevTab=(*Session)->CurrTab;
		(*Session)->LastTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->LastTab->NextTab=(*Session)->CurrTab;
		(*Session)->CurrTab->PrevTab=(*Session)->LastTab;
		(*Session)->LastTab=(*Session)->CurrTab;
	}
	else if ((*Session)->CurrTab==(*Session)->FirstTab)
	{
		
		(*Session)->LastTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->LastTab;
		(*Session)->CurrTab->PrevTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab->NextTab->PrevTab=(*Session)->CurrTab;
		(*Session)->CurrTab->NextTab=(*Session)->CurrTab->NextTab->NextTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab;
		(*Session)->FirstTab=(*Session)->CurrTab->PrevTab;
	}
	else
	{
		
		(*Session)->CurrTab->NextTab->NextTab->PrevTab=(*Session)->CurrTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab->PrevTab=(*Session)->CurrTab->NextTab;
	
		(*Session)->CurrTab->NextTab=(*Session)->CurrTab->NextTab->NextTab;//
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab;
		
	}
}


void SessionTabClose(InfoSessionPtr* Session)
{
	assert(*Session!=NULL);
	//deleting all sites from current tab
	SiteNodePtr del=(*Session)->CurrTab->FirstSite;
	SiteNodePtr start=del;
	while(1)
	{
		del=del->NextSite;
		free(start->Address);
		free(start);
		start=del;
		if(del==NULL)
			break;
	}
	//Method for Tabclosing similarly to the number of Tabs
	if((*Session)->FirstTab==(*Session)->LastTab)//The case i have only one Tab
	{
		TabNodePtr delTab=(*Session)->CurrTab;
		free(delTab);
		free((*Session)->OpeningAddress);
		free(*Session);
		*Session=NULL;
		return ;
	}
	if((*Session)->CurrTab->NextTab==(*Session)->CurrTab->PrevTab)//The case i have only two Tabs
	{
		if((*Session)->CurrTab==(*Session)->FirstTab)
		{
			(*Session)->FirstTab=(*Session)->LastTab;
			TabNodePtr delNode=(*Session)->CurrTab;
			(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
			(*Session)->CurrTab->NextTab=NULL;
			(*Session)->CurrTab->PrevTab=NULL;
			free(delNode);
		}
		else
		{
			(*Session)->LastTab=(*Session)->FirstTab;
			TabNodePtr delNode=(*Session)->CurrTab;
			(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
			(*Session)->CurrTab->NextTab=NULL;
			(*Session)->CurrTab->PrevTab=NULL;
			free(delNode);
		}
		return ;
	}
	if((*Session)->CurrTab==(*Session)->FirstTab)//The case i have Tabs more than two 
	{
		(*Session)->FirstTab=(*Session)->CurrTab->NextTab;
		TabNodePtr delNode=(*Session)->CurrTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
		free(delNode);
	}
	else if((*Session)->CurrTab==(*Session)->LastTab)
	{
		(*Session)->LastTab=(*Session)->CurrTab->PrevTab;
		TabNodePtr delNode=(*Session)->CurrTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
		free(delNode);
	}
	else
	{
		TabNodePtr delNode=(*Session)->CurrTab;
		(*Session)->CurrTab->PrevTab->NextTab=(*Session)->CurrTab->NextTab;
		(*Session)->CurrTab->NextTab->PrevTab=(*Session)->CurrTab->PrevTab;
		(*Session)->CurrTab=(*Session)->CurrTab->NextTab;
		free(delNode);
	}
}

void SessionClose(InfoSessionPtr* Session)
{
	assert(*Session!=NULL);
	//Here i delete only the sites from all tabs
	TabNodePtr Del=(*Session)->FirstTab;
	while(1)
	{
		SiteNodePtr ft=Del->FirstSite;
		SiteNodePtr start=ft;
		while(start!=NULL)
		{
			ft=ft->NextSite;
			free(start->Address);
			free(start);
			start=ft;
		}
		if(Del==(*Session)->LastTab)
			break;
		Del=Del->NextTab;
	}
	//Here i delete all the tabs
	if((*Session)->FirstTab==(*Session)->LastTab)//The case i have only one tab in InfoSession
		free((*Session)->FirstTab);
	else
	{
		TabNodePtr DelTab=(*Session)->FirstTab;
		TabNodePtr EndTab=(*Session)->LastTab;
		TabNodePtr Delstart=Del;
		while(1)
		{	
			DelTab=DelTab->NextTab;
			free(Delstart);
			Delstart=DelTab;
			if(DelTab==EndTab)
			{
				DelTab=DelTab->NextTab;
				free(DelTab);
				break;
			}
		}
	}
	//Here i delete the InfoSession
	free((*Session)->OpeningAddress);
	free(*Session);
	*Session=NULL;
}

void SessionNewAddress(InfoSessionPtr* Session,char* Address)
{
	assert(*Session!=NULL);
	SiteNodePtr Site=malloc(sizeof(struct SiteNode));
	Site->Address=malloc(sizeof(strlen(Address))+1);
	strcpy(Site->Address,Address);
	if((*Session)->CurrTab->CurrSite->NextSite!=NULL)//i have two Tabs or more 
	{
		SiteNodePtr del=(*Session)->CurrTab->CurrSite->NextSite;
		SiteNodePtr start=del;
		while(1)
		{
			del=del->NextSite;
			free(start->Address);
			free(start);
			start=del;
			if(start==NULL)
				break;
		}
	}
	Site->UpTab=(*Session)->CurrTab;
	(*Session)->CurrTab->CurrSite->NextSite=Site;
	Site->PrevSite=(*Session)->CurrTab->CurrSite;
	Site->NextSite=NULL;
	(*Session)->CurrTab->CurrSite=Site;
}

void SessionOpenNewTab(InfoSessionPtr* Session)
{
	TabNodePtr Tab=malloc(sizeof(struct TabNode));
	
	
}
