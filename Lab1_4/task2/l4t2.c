/* Robert Aroutiounian
   Lab 4 task 2
   9/26/16
*/

/*
 
 Compile with: gcc -o l4t2 l4t2.c -I/usr/include/libxml2 -lxslt -lxml2
 
 */

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>

int des = 0;

void error(const char *msg)
{
   fprintf(stderr, "ERROR: %s\n", msg);
   exit(1);
}

int is_valid(const xmlDocPtr doc, const char *schema_filename)
{
   xmlDocPtr schema_doc = xmlReadFile(schema_filename, NULL, XML_PARSE_NONET);
   if (schema_doc == NULL) {
      error("Failed to load XML schema.");
   }
   
   // See API at: http://xmlsoft.org/html/libxml-xmlschemas.html
   
   xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewDocParserCtxt(schema_doc);
   if (parser_ctxt == NULL) {
      error("Failed to create parsing context.");
   }
   
   xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
   if (schema == NULL) {
      error("XML Schema in invalid.");
   }
   
   xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
   if (valid_ctxt == NULL) {
      error("Failed to create validation context.");
   }
   
   int is_valid = (xmlSchemaValidateDoc(valid_ctxt, doc) == 0);
   
   xmlSchemaFreeValidCtxt(valid_ctxt);
   xmlSchemaFree(schema);
   xmlSchemaFreeParserCtxt(parser_ctxt);
   xmlFreeDoc(schema_doc);
   
   return is_valid;
}

void printElements(xmlNode *aNode)
{
   xmlNode *curNode = NULL;

	for (curNode = aNode; curNode; curNode = curNode->next) {
        // if (curNode->type == XML_ELEMENT_NODE) {
        //     printf("node type: Element, name: %s\n", curNode->name);
        // }
        if (curNode->type == XML_TEXT_NODE)
        {
            if (strcmp((char *)(curNode->parent)->name, "season") == 0)
            {
               printf("\n%s", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "year") == 0)
            {
               printf("%s\n", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "programName") == 0)
            {
               printf("\n%-4s", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "courseName") == 0)
            {
               printf("%-45s", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "courseNumber") == 0)
            {
               printf("%-10s", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "unitWeight") == 0)
            {
               printf("UNIT WEIGHT: %s\n", curNode->content);
            }
            if (des == 1 && strcmp((char *)(curNode->parent)->name, "description") == 0)
            {
               printf("%s\n", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "instructor") == 0)
            {
               printf("\t%-43s", curNode->content);
            }
            if (strcmp((char *)(curNode->parent)->name, "time") == 0)
            {
               printf("%s\n", curNode->content);
            }
        }
        printElements(curNode->children);
    }
}

void print_catalog(xmlDocPtr doc)
{
   xmlNode *root_node = xmlDocGetRootElement(doc);
   
   printElements(root_node);
   
   // USE NAVIGATION FROM libxml2 API
   // http://xmlsoft.org/html/libxml-tee.html
}

int main(int argc, char **argv)
{
   (void) argc;
   (void) argv;
   
   if (argc < 3)
   {
      printf("Usage: l11q1 <xml file> <schema file>\n");
      exit(1);
   }
   
   if (argc > 3)
   {
      if (strcmp(argv[3], "-d") == 0)
      {
         des = 1;
      }
   }
   // see API at: http://xmlsoft.org/html/libxml-parser.html
   
   printf("Loading %s\n", argv[1]);
   xmlDocPtr doc = xmlReadFile(argv[1], NULL, XML_PARSE_NONET | XML_PARSE_NOBLANKS);
   if (doc == NULL) {
      error("Failed to load.");
   }
   printf("Loaded.\n");
   
   printf("Validating with %s\n", argv[2]);
   if (!is_valid(doc, argv[2])) {
      error("Failed to validate.");
   }
   printf("Validated.\n");
   
   printf("CI SCHEDULE\n");
   print_catalog(doc);
   
   xmlFreeDoc(doc);
   
   return 0;
}
