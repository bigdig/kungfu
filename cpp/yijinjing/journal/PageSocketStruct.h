/*****************************************************************************
 * Copyright [2017] [taurus.ai]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

/**
 * Structs for page engine socket communication.
 * @Author cjiang (changhao.jiang@taurus.ai)
 * @since   September, 2017
 */

#ifndef YIJINJING_PAGESOCKETSTRUCT_H
#define YIJINJING_PAGESOCKETSTRUCT_H

#include "constants.h"
#include <boost/array.hpp>

#define PAGED_SOCKET_FILE KUNGFU_SOCKET_FOLDER + "paged.sock"
#define PAGED_SOCKET_PORT 10086

YJJ_NAMESPACE_START

#define SOCKET_MESSAGE_MAX_LENGTH       500 /**< max length of a socket buffer */
#define SOCKET_ERROR_MAX_LENGTH         100 /**< max length of error msg for socket */

//////////////////////////////////////////
/// (byte) PagedSocketTypeConstants
//////////////////////////////////////////
// register / exit 10 ~ 19
#define PAGED_SOCKET_JOURNAL_REGISTER   11 /**< register journal */
#define PAGED_SOCKET_READER_REGISTER    12 /**< register client (reader) */
#define PAGED_SOCKET_WRITER_REGISTER    13 /**< register client (writer) */
#define PAGED_SOCKET_CLIENT_EXIT        19 /**< exit a client */
// timer req
#define TIMER_SEC_DIFF_REQUEST          99 /**< timer update request */

/**
 * Socket Request msg, fully utilized by "register"
 */
struct PagedSocketRequest
{
    /** PagedSocketTypeConstants */
    int8_t    type;
    /** process id (only utilized when registering client) */
    int32_t     pid;
    /** process id (only take effect when exiting client) */
    int32_t     hash_code;
    /** source id (only take effect when login trade engine) */
    int16_t   source;
    /** name utilized for CLIENT / JOURNAL / STRATEGY */
    string    name;
};

struct PagedSocketResponse
{
    /** PagedSocketTypeConstants */
    int8_t    type;
    /** return true if success */
    bool    success;
    /** error message */
    string    error_msg;
};

struct PagedSocketRspClient: public PagedSocketResponse
{
    /** memory_msg_file is provided for further page usage */
    string    memory_msg_file;
    /** size of comm_file */
    int32_t     file_size;
    /** hash code of this client */
    int32_t     hash_code;
};

struct PagedSocketRspJournal: public PagedSocketResponse
{
    /** the index in the memory message buffer */
    int32_t     memory_msg_idx;
};

struct PagedSocketRspStrategy: public PagedSocketResponse
{
    /** start of request id */
    int32_t     rid_start;
    /** end of request id */
    int32_t     rid_end;
};

typedef boost::array<char, SOCKET_MESSAGE_MAX_LENGTH> PagedSocketRequestBuf;
typedef boost::array<char, SOCKET_MESSAGE_MAX_LENGTH> PagedSocketResponseBuf;

YJJ_NAMESPACE_END

#endif //YIJINJING_PAGESOCKETSTRUCT_H
