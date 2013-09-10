
/******************************************************************************
 *
 * nglogc - Flexible C Logging API
 *
 * Author:        Dennis Krzyzaniak
 * E-mail:        ebrosius@netgarage.org
 * WWW:           http://www.netgarage.org
 * Copyright (C): 2010 by Dennis Krzyzaniak
 *
 * This file is part of nglogc.
 *
 * nglogc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * nglogc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with nglogc.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

/* =========== INCLUDES ==================================================== */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "log_record.h"

#include "timestamp.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* =========== MODULE CONFIGURATION ======================================== */
/* =========== DEFINES ===================================================== */

#define MAX_INT   10

/* =========== DATA TYPES ================================================== */
/* =========== GLOBALS ===================================================== */
/* =========== PRIVATE PROTOTYPES ========================================== */

static void
clean_record(
      logRecord_t* rec
      );


static void
timestamp_record(
      logRecord_t* rec
      );

/* =========== PUBLIC FUNCTIONS ============================================ */

/*---------------------------------------------------------------------------*/
logc_error_t
newLogRecord(
      logRecord_t* rec
      )
{
   logc_error_t err = LOG_ERR_OK;

   if (rec == NULL) {
      err = LOG_ERR_NULL;
   }

   if (err == LOG_ERR_OK) {
      rec->newRecord = NULL;
      switch (rec->rtype) {
         case CLEAN:
            clean_record(rec);
            break;
         case TIMESTAMP:
            timestamp_record(rec);
            break;
         default:
            err = LOG_ERR_PARAM;
            break;
      }
   }

   if (err == LOG_ERR_OK) {
      if (rec->newRecord == NULL) {
         err = LOG_ERR_MEM;
      }
   }

   return err;
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
void
deleteLogRecord(
      logRecord_t* rec
      )
{
   if (rec != NULL) {
      if (rec->newRecord != NULL) {
         free(rec->newRecord);
      }
   }
}
/*---------------------------------------------------------------------------*/

/* =========== PRIVATE FUNCTIONS =========================================== */

/*---------------------------------------------------------------------------*/
static void
clean_record(
      logRecord_t* rec
      )
{
   int recordSize = 0;
   logc_bool_t flf = LOG_FALSE;

   if (rec->file == NULL) {
      recordSize = (int)(strlen(rec->formatStr) + 2);
   } else {
      flf = LOG_TRUE;
      recordSize = (int)(strlen(rec->file) + MAX_INT + strlen(rec->function) +
         strlen(rec->formatStr) + strlen(":  - ") + 2);
   }
   rec->newRecord = malloc(recordSize);

   if (rec->newRecord != NULL) {
      memset(rec->newRecord, 0, recordSize);
      if (flf == LOG_TRUE) {
         sprintf(rec->newRecord, "%s:%d %s - ",
               rec->file, rec->line, rec->function);
      }
      strcat(rec->newRecord + strlen(rec->newRecord), rec->formatStr);
#if 0
      vsprintf(rec->newRecord + strlen(rec->newRecord),
            rec->formatStr, *(rec->vaList));
#endif

      rec->newRecord[strlen(rec->newRecord)] = '\n';
   }
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
static void
timestamp_record(
      logRecord_t* rec
      )
{
   const char* timest = "day mon dd hh:mm:ss YYYY : ";
   int recordSize = 0;
   logc_bool_t flf = LOG_FALSE;

   if (rec->file == NULL) {
      recordSize = (int)(strlen(rec->formatStr) + strlen(timest) + 2);
   } else {
      flf = LOG_TRUE;
      recordSize = (int)(strlen(rec->file) + MAX_INT + strlen(rec->function) +
         strlen(rec->formatStr) + strlen(timest) + strlen(":  - ") + 2);
   }
   rec->newRecord = malloc(recordSize);

   if (rec->newRecord != NULL) {
      memset(rec->newRecord, 0, recordSize);
      strcpy(rec->newRecord, timest);
      addTimestamp(rec->newRecord);
      if (flf == LOG_TRUE) {
         sprintf(rec->newRecord + strlen(rec->newRecord), "%s:%d %s - ",
               rec->file, rec->line, rec->function);
      }
      strcat(rec->newRecord + strlen(rec->newRecord), rec->formatStr);
#if 0
      vsprintf(rec->newRecord + strlen(rec->newRecord),
            rec->formatStr, *(rec->vaList));
#endif

      rec->newRecord[strlen(rec->newRecord)] = '\n';
   }
}
/*---------------------------------------------------------------------------*/

/* ========================== END OF FILE ================================== */

/*
 * vim settings, please do not remove!
 * vim:autoindent:
 * vim:ts=3:sw=3:sts=3:expandtab:cindent:tw=75:formatoptions=croql:
 * vim600:foldmethod=syntax:
 */
