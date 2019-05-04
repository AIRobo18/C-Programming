/* Robert Aroutiounian
   Lab 4 task 1
   9/26/16
*/

#include <stdio.h>
#include <string.h>
//#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
#define MAX_NAME 128

int catalog = 0; 
int semester = 0;
int season = 0;
int year = 0;
int major = 0;
int course = 0;
int programName = 0;
int courseName = 0;
int courseNumber = 0;
int unitWeight = 0;
int description = 0;
int instructor = 0;
int time = 0;
int newLine = 0;
int tab = 0;
int end = 0;
int tab2 = 0;
int des = 0;
int end1 = 0;
int newLine2 = 0;

xmlParserInputPtr resolveEntity(void *user_data, const xmlChar *publicId, const xmlChar *systemId)
{
   // printf("resolveEntity(publicId='%s', systemId='%s')\n", publicId, systemId);
   fflush(stdout);
   return NULL;
}

void internalSubset(void *user_data, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID)
{
   // printf("internalSubset(name='%s', ExternalID='%s', SystemID='%s')\n", name, ExternalID, SystemID);
   fflush(stdout);
}

void externalSubset(void *user_data, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID)
{
   // printf("externalSubset(name='%s', ExternalID='%s', SystemID='%s')\n", name, ExternalID, SystemID);
   fflush(stdout);
}

xmlEntityPtr getEntity(void *user_data, const xmlChar *name)
{
   // printf("getEntity(name='%s')\n", name);
   fflush(stdout);
   return NULL;
}

xmlEntityPtr getParameterEntity(void *user_data, const xmlChar *name)
{
   // printf("getParameterEntity(name='%s')\n", name);
   fflush(stdout);
   return NULL;
}

void entityDecl(void *user_data, const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId, xmlChar *content)
{
   // printf("entityDecl(name='%s', type=%i, publicId='%s', systemId='%s', content='%s')\n", name, type, publicId, systemId, content);
   fflush(stdout);
}

void notationDecl(void *user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId)
{
   // printf("notationDecl(name='%s', publicId='%s', systemId='%s')\n", name, publicId, systemId);
   fflush(stdout);
}

void attributeDecl(void *user_data, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree)
{
   (void)tree;
   // printf("attributeDecl(elem='%s', fullname='%s', type=%i, def=%i, defaultValue='%s')\n", elem, fullname, type, def, defaultValue);
   fflush(stdout);
}

void elementDecl(void *user_data, const xmlChar *name, int type, xmlElementContentPtr content)
{
   (void)content;
   // printf("elementDecl(name='%s', type=%i)\n", name, type);
   fflush(stdout);
}

void unparsedEntityDecl(void *user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
   // printf("unparsedEntityDecl(name='%s', publicId='%s', systemId='%s', notationName='%s')\n", name, publicId, systemId, notationName);
   fflush(stdout);
}

void setDocumentLocator(void *user_data, xmlSAXLocatorPtr loc)
{
   (void)loc;
   // printf("setDocumentLocator()\n");
   fflush(stdout);
}

void startDocument(void *user_data)
{
   // printf("startDocument()\n");
   fflush(stdout);
}

void endDocument(void *user_data)
{
   // printf("endDocument()\n");
   fflush(stdout);
}

void startElement(void *user_data, const xmlChar *name, const xmlChar **atts)
{
	if (strcmp((char *)name, "catalog") == 0)
	{
		//printf("catalog is 1\n");
		catalog = 1;
	}
	else if (strcmp((char *)name, "semester") == 0)
	{
		//printf("&&&&&&&&&& SEMESTER IS 1\n");
		semester = 1;
	}
	else if (strcmp((char *)name, "season") == 0)
	{
		season = 1;
	}
	else if (strcmp((char *)name, "year") == 0)
	{
		year = 1;
	}
	else if (strcmp((char *)name, "major") == 0)
	{
		major = 1;
	}
	else if (strcmp((char *)name, "course") == 0)
	{
		course = 1;
	}
	else if (strcmp((char *)name, "programName") == 0)
	{
		programName = 1;
	}
	else if (strcmp((char *)name, "courseName") == 0)
	{
		courseName = 1;
	}
	else if (strcmp((char *)name, "courseNumber") == 0)
	{
		courseNumber = 1;
	}
	else if (strcmp((char *)name, "unitWeight") == 0)
	{
		unitWeight = 1;
	}
   else if (des == 1 && strcmp((char *)name, "description") == 0)
   {
      description = 1;
   }
	else if (strcmp((char *)name, "instructor") == 0)
	{
		instructor = 1;
	}
	else if (strcmp((char *)name, "time") == 0)
	{
		time = 1;
	}
   int i;
   //printf("startElement(name='%s', atts=", name);
   //printf("%s ", name);
   fflush(stdout);
   if (atts != NULL) {
      //printf("{");
      fflush(stdout);
      for (i = 0; atts[i] != NULL; i++) {
         //printf("'%s'", atts[i]);
         fflush(stdout);
         if (atts[i + 1] != NULL) {
            //printf(", ");
         }
      }
      //printf("}");
      fflush(stdout);
   } else {
      //printf("NULL");
      fflush(stdout);
   }
   //printf(")\n");
   fflush(stdout);
}

void endElement(void *user_data, const xmlChar *name)
{
   //printf("endElement(name='%s')\n", name);
	if (strcmp((char *)name, "catalog") == 0)
	{
		//printf("catalog is 0\n");
		catalog = 0;
	}
	else if (strcmp((char *)name, "semester") == 0)
	{
		//printf("$$$$$$$$$$$$$$$$$$$$ SEMESTER IS 0\n");
		semester = 0;
		fflush(stdout);
	}
	else if (strcmp((char *)name, "season") == 0)
	{
		season = 0;
	}
	else if (strcmp((char *)name, "year") == 0)
	{
		year = 0;
	}
	else if (strcmp((char *)name, "major") == 0)
	{
		major = 0;
	}
	else if (strcmp((char *)name, "course") == 0)
	{
		course = 0;
	}
	else if (strcmp((char *)name, "programName") == 0)
	{
		programName = 0;
	}
	else if (strcmp((char *)name, "courseName") == 0)
	{
		courseName = 0;
	}
	else if (strcmp((char *)name, "courseNumber") == 0)
	{
		courseNumber = 0;
	}
	else if (strcmp((char *)name, "unitWeight") == 0)
	{
		unitWeight = 0;
	}
   else if (des == 1 && strcmp((char *)name, "description") == 0)
   {
      description = 0;
   }
	else if (strcmp((char *)name, "instructor") == 0)
	{
		instructor = 0;
	}
	else if (strcmp((char *)name, "time") == 0)
	{
		time = 0;
	}
   fflush(stdout);
}

void attribute(void *user_data, const xmlChar *name, const xmlChar *value)
{
   // printf("attribute(name='%s', value='%s')\n", name, value);
   fflush(stdout);
}

void reference(void *user_data, const xmlChar *name)
{
   // printf("reference(name='%s')\n", name);
   fflush(stdout);
}

void characters(void *user_data, const xmlChar *ch, int len)
{
   char *ptr_ch = (char *) ch;
   while (len-- > 0)
   {
      // if (strchr("\t", *ptr_ch) == NULL)
      // putchar(*ptr_ch);
      // ptr_ch++;
      if (catalog == 1)
      {
      	printf("CI SCHEDULE\n\n");
      	catalog = 0;
      }
      if (semester == 1)
      {
      	//printf("Inside semester\n");
     //  	if (strchr("\n", *ptr_ch) != NULL)
	    // putchar(*ptr_ch);
	    // ptr_ch++;
	    tab2 = 1;
      }
      if (season == 1)
      {
      	//printf("insdie season\n");
      	if (strchr("\n\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      }
      if (year == 1)
      {
      	if (strchr("\n\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      	newLine = 1;
      }
      if (year == 0 && programName == 1 && newLine == 1)
      {
      	printf("\n\n");
      	newLine = 0;
      }
      if (programName == 1)
      {
      	if (strchr("\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      }
      if (courseName == 1)
      {
      	if (strchr("\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      }
      if (courseNumber == 1)
      {
      	if (strchr("\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      	tab = 1;
      }
      if (courseNumber == 0 && unitWeight == 1 && tab == 1)
      {
      	printf("\t\t UNIT WEIGHT: ");
      	tab = 0;
      }
      if (unitWeight == 1)
      {
      	if (strchr("\n\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      	newLine = 1;
      }
      if (unitWeight == 0 && des == 0 && instructor == 1 && newLine == 1)
      {
      	printf("\n\t");
      	newLine = 0;
      }
      if (unitWeight == 0 && des == 1 && description == 1 && newLine ==1)
      {
         printf("\n");
         newLine = 0;
      }
      if (description == 1 && des == 1)
      {
         if (strchr("\n\t", *ptr_ch) == NULL)
         putchar(*ptr_ch);
         ptr_ch++;
         newLine2 = 1;
      }
      if (description == 0 && instructor == 1 && newLine2 == 1)
      {
         printf("\n\t");
         newLine2 = 0;
      }
      if (instructor == 1)
      {
      	//if (strchr("\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      	tab = 1;
      }
      if (instructor == 0 && time == 1 && tab == 1)
      {
      	printf("\t\t");
      	tab = 0;
      }
      if (time == 1)
      {
      	if (strchr("\t", *ptr_ch) == NULL)
      	putchar(*ptr_ch);
      	ptr_ch++;
      	end = 1;
         end1 = 1;
      }
      if (des == 1 && time == 0 && end1 == 1)
      {
         printf("\n");
         end1 = 0;
      }
      if (time == 0 && end == 1)
      {
      	printf("\n");
      	end = 0;
      }
      if (semester == 0 && tab2 == 1)
      {
      	// if (strchr("\n", *ptr_ch) == NULL)
      	// putchar(*ptr_ch);
      	// ptr_ch++;
      	printf("\n");
      	tab2 = 0;
      }
   }
   
   fflush(stdout);
}

void ignorableWhitespace(void *user_data, const xmlChar *ch, int len)
{
   
   char real_ch[len + 1];
   strncpy(real_ch, (char*)ch, len);
   real_ch[len] = 0;
   
   // printf("ignorableWhitespace(ch='%s', len=%i)\n", ch, len);
   fflush(stdout);
}

void processingInstruction(void *user_data, const xmlChar *target, const xmlChar *data)
{
   // printf("processingInstruction(target='%s', data='%s')\n", target, data);
   fflush(stdout);
}

void comment(void *user_data, const xmlChar *value)
{
   // printf("comment(value='%s')\n", value);
   fflush(stdout);
}

void cdataBlock(void *user_data, const xmlChar *value, int len)
{
   // printf("cdataBlock(value='%s', len=%i)\n", value, len);
   fflush(stdout);
}

void warning(void *user_data, const char *msg, ...)
{
   // printf("warning(msg='%s', ...)\n", msg);
   fflush(stdout);
}

void error(void *user_data, const char *msg, ...)
{
   // printf("error(msg='%s', ...)\n", msg);
   fflush(stdout);
}

void fatalError(void *user_data, const char *msg, ...)
{
   // printf("fatalError(msg='%s', ...)\n", msg);
   fflush(stdout);
}

int isStandalone(void *user_data)
{
   // printf("isStandalone()\n");
   fflush(stdout);
   return 1;
}

int hasInternalSubset(void *user_data)
{
   // printf("hasInternalSubset()\n");
   fflush(stdout);
   return 1;
}

int hasExternalSubset(void *user_data)
{
   // printf("hasExternalSubset()\n");
   fflush(stdout);
   return 1;
}

void startElementNs(void *user_data, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI, int nb_namespaces, const xmlChar **namespaces, int nb_attributes, int nb_defaulted, const xmlChar **attributes)
{
   int i;
   // printf("startElementNs(localname='%s', prefix='%s', URI='%s', nb_namespaces=%i, namespaces={", localname, prefix, URI, nb_namespaces);
   fflush(stdout);
   for (i = 0; i < nb_namespaces; i++) {
      // printf("'%s'", namespaces[i]);
      fflush(stdout);
      if (i + 1 < nb_namespaces) {
         // printf(", ");
      }
   }
   // printf("}, nb_attributes=%i, nb_defaulted=%i, attributes={", nb_attributes, nb_defaulted);
   fflush(stdout);
   for (i = 0; i < nb_attributes; i++) {
      // printf("'%s'", attributes[i]);
      fflush(stdout);
      if (i + 1 < nb_attributes) {
         // printf(", ");
      }
   }
   // printf("})\n");
   fflush(stdout);
}

void endElementNs(void *user_data, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI)
{
   // printf("endElementNs(localname='%s', prefix='%s', URI='%s')\n", localname, prefix, URI);
   fflush(stdout);
}

void serror(void *userData, xmlErrorPtr error)
{
   (void)userData;
   (void)error;
   // printf("serror()\n");
   fflush(stdout);
}


xmlSAXHandler saxHandler = {
   .internalSubset =  internalSubset,
   .isStandalone =  isStandalone,
   .hasInternalSubset =  hasInternalSubset,
   .hasExternalSubset =  hasExternalSubset,
   .resolveEntity =  resolveEntity,
   .getEntity =  getEntity,
   .entityDecl =  entityDecl,
   .notationDecl =  notationDecl,
   .attributeDecl =  attributeDecl,
   .elementDecl =  elementDecl,
   .unparsedEntityDecl =  unparsedEntityDecl,
   .setDocumentLocator =  setDocumentLocator,
   .startDocument =  startDocument,
   .endDocument =  endDocument,
   .startElement =  startElement,
   .endElement =  endElement,
   .reference =  reference,
   .characters =  characters,
   .ignorableWhitespace =  ignorableWhitespace,
   .processingInstruction =  processingInstruction,
   .comment =  comment,
   .warning =  warning,
   .error =  error,
   .fatalError =  fatalError,
   .getParameterEntity =  getParameterEntity,
   .cdataBlock =  cdataBlock,
   .externalSubset =  externalSubset,
   .startElementNs =  startElementNs,
   .endElementNs =  endElementNs,
   .serror =  serror,
   .initialized =  1,
};


int main(int argc, char **argv)
{
   if (argc < 2 || argc > 4) {
      fprintf(stderr, "Syntax: %s [document.xml]\n", argv[0]);
      return 1;
   }
   
   if (argc > 2)
   {
      if (strcmp(argv[2], "-d") == 0) {
         des = 1;
      }
   }
   
   //printf("%s", argv[2]);
   fprintf(stderr, "Runnig for: %s\n", argv[1]);
   xmlKeepBlanksDefault(0);
   xmlSAXUserParseFile(&saxHandler, NULL, argv[1]);
   fprintf(stderr, "Done with: %s\n", argv[1]);

   return 0;
}
