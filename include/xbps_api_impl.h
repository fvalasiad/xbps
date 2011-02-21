/*-
 * Copyright (c) 2010-2011 Juan Romero Pardines.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *-
 */

#ifndef _XBPS_API_IMPL_H_
#define _XBPS_API_IMPL_H_

#ifndef DEBUG
#  define NDEBUG
#endif
#include <assert.h>
#include <archive.h>
#include <archive_entry.h>

#include <xbps_api.h>

#define ARCHIVE_READ_BLOCKSIZE	10240

#define EXTRACT_FLAGS	ARCHIVE_EXTRACT_SECURE_NODOTDOT | \
			ARCHIVE_EXTRACT_SECURE_SYMLINKS
#define FEXTRACT_FLAGS	ARCHIVE_EXTRACT_OWNER | ARCHIVE_EXTRACT_PERM | \
			ARCHIVE_EXTRACT_TIME | EXTRACT_FLAGS

#ifndef __UNCONST
#define __UNCONST(a)	((void *)(unsigned long)(const void *)(a))
#endif

/*
 * By default all public functions have default visibility, unless
 * visibility has been detected by configure and the HIDDEN definition
 * is used.
 */
#if HAVE_VISIBILITY
#define HIDDEN __attribute__ ((visibility("hidden")))
#else
#define HIDDEN
#endif

/**
 * @def XBPS_FETCH_CACHECONN
 *
 * Default (global) limit of cached connections used in libfetch.
 */
#define XBPS_FETCH_CACHECONN            6

/**
 * @def XBPS_FETCH_CACHECONN_HOST
 *
 * Default (per host) limit of cached connections used in libfetch.
 */
#define XBPS_FETCH_CACHECONN_HOST       2

__BEGIN_DECLS

/**
 * @private
 * From lib/initend.c
 */
struct xbps_handle HIDDEN *xbps_handle_get(void);

/**
 * @private
 * From lib/download.c
 */
void HIDDEN xbps_fetch_set_cache_connection(int global, int per_host);
void HIDDEN xbps_fetch_unset_cache_connection(void);

/**
 * @private
 * From lib/package_config_files.c
 */
int HIDDEN xbps_entry_is_a_conf_file(prop_dictionary_t, const char *);
int HIDDEN xbps_entry_install_conf_file(prop_dictionary_t,
					struct archive_entry *,
					const char *,
					const char *,
					const char *);
/**
 * @private
 * From lib/plist_entry.c
 */
prop_dictionary_t HIDDEN
	xbps_read_dict_from_archive_entry(struct archive *ar,
					  struct archive_entry *entry);

/**
 * @private
 * From lib/package_remove_obsoletes.c
 */
int HIDDEN xbps_remove_obsoletes(prop_dictionary_t, prop_dictionary_t);

/**
 * @private
 * From lib/repository_finddeps.c
 */
int HIDDEN xbps_repository_find_pkg_deps(prop_dictionary_t,
					 prop_array_t,
					 prop_dictionary_t);

/**
 * @private
 * From lib/package_requiredby.c
 */
int HIDDEN xbps_requiredby_pkg_add(prop_array_t, prop_dictionary_t);
int HIDDEN xbps_requiredby_pkg_remove(const char *);

/**
 * @private
 * From lib/transaction_sortdeps.c
 */
int HIDDEN xbps_sort_pkg_deps(void);

/**
 * @private
 * From lib/transaction_dictionary.c
 */
prop_dictionary_t HIDDEN xbps_transaction_dictionary_get(void);

/**
 * @private
 * From lib/repository_sync_index.c
 */
char HIDDEN *xbps_get_remote_repo_string(const char *);

/**
 * @private
 * From lib/fexec.c
 */
int HIDDEN xbps_file_exec(const char *arg, ...);
int HIDDEN xbps_file_exec_skipempty(const char *arg, ...);
int HIDDEN xbps_file_chdir_exec(const char *path, const char *arg, ...);

/**
 * @private
 * From lib/package_replaces.c
 */
int HIDDEN xbps_repository_pkg_replaces(prop_dictionary_t,
					prop_dictionary_t);

/**
 * @private
 * From lib/plist_find.c
 */
prop_dictionary_t HIDDEN
	xbps_find_virtualpkg_user_in_dict_by_name(prop_dictionary_t,
						  const char *,
						  const char *);
prop_dictionary_t HIDDEN
	xbps_find_virtualpkg_user_in_dict_by_pattern(prop_dictionary_t,
						     const char *,
						     const char *);

__END_DECLS

#endif /* !_XBPS_API_IMPL_H_ */
