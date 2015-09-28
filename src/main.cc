/*$Id: main.cc 2015/01/21 al $ -*- C++ -*-
 * Copyright (C) 2001 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 * top level module
 * it all starts here
 */
#include "globals.h"
#include "u_prblst.h"
#include "u_sim_data.h"
#include "e_cardlist.h"
#include "u_lang.h"
#include "ap.h"
#include "patchlev.h"
#include "c_comand.h"
#include "declare.h"	/* plclose */
#include "config.h"
#include "startup.h"
// #define COMMENT_CHAR "*"
using namespace std;
/*--------------------------------------------------------------------------*/
 extern char *optarg;
        extern int optind, opterr, optopt;
           #include <getopt.h>

/*--------------------------------------------------------------------------*/
struct JMP_BUF{
  sigjmp_buf p;
} env;
/*--------------------------------------------------------------------------*/
static void sign_on(void)
{
  if (OPT::quiet) return;
  IO::mstdout <<
    "Gnucap : The Gnu Circuit Analysis Package\n"
    "Never trust any version less than 1.0\n"
    "Copyright 1982-2015, Albert Davis\n"
    "Copyright 2009-2015, Felix Salfelder\n"
    "Gnucap comes with ABSOLUTELY NO WARRANTY\n"
    "This is free software, and you are welcome\n"
    "to redistribute it under the terms of \n"
    "the GNU General Public License, version 3 or later.\n"
    "See the file \"COPYING\" for details.\n"
#ifdef HAVE_GIT_REPO
    "main version: " PATCHLEVEL "\n"
#else
    "main version: " VERSION "\n"
#endif
    "core-lib version: " << lib_version() << "\n";  
}
/*--------------------------------------------------------------------------*/
void read_startup_files(void)
{
  trace0("read_startup_files");
  string name = findfile(SYSTEMSTARTFILE, SYSTEMSTARTPATH, R_OK);
  if (name != "") {untested();
    trace1("read_startup_files", name);
    try{
      CMD::command("get " + name, &CARD_LIST::card_list);
    } catch(Exception e){
      error(bDANGER, "%s\n",e.message().c_str());
    }
  }else{
  }
  if (!startup_recursive()) {
    trace1("read_startup_files, no cwd", name);
    name = findfile(USERSTARTFILE, USERSTARTPATH, R_OK);
    if (name != "") {untested();
      try{
        CMD::command("get " + name, &CARD_LIST::card_list);
      } catch(Exception e){
        error(bDANGER, "%s\n",e.message().c_str());
      }
    }else{
    }
  }
  trace0("clear");
  try{
    CMD::command("clear", &CARD_LIST::card_list);
  } catch(Exception e){
    error(bDANGER, "%s\n",e.message().c_str());
  }
  if (!OPT::language) {
      try{
        CMD::command(std::string("options lang=") + DEFAULT_LANGUAGE, &CARD_LIST::card_list);
      } catch(Exception e){
        error(bDANGER, "%s\n",e.message().c_str());
      }
  }else{
  }
}
/*--------------------------------------------------------------------------*/
/* sig_abrt: trap asserts
 */
extern "C" {
  static void sig_abrt(SIGNALARGS)
  {
    signal(SIGINT,sig_abrt);
    static int count = 10;
    if (--count > 0) {
      error(bDANGER, "\n");
    }else{untested();
      exit(1);
    }
  }
}
/*--------------------------------------------------------------------------*/
/* sig_int: what to do on receipt of interrupt signal (SIGINT)
 * cancel batch files, then back to command mode.
 * (actually, control-c trap)
 */
extern "C" {
  static void sig_int(SIGNALARGS)
  {
    signal(SIGINT,sig_int);
    if (ENV::run_mode == rBATCH) {
      exit(1);
    }else{
      IO::error << '\n';
      siglongjmp(env.p,1);
    }
  }
}
/*--------------------------------------------------------------------------*/
extern "C" {
  static void sig_fpe(SIGNALARGS)
  {
    untested();
    signal(SIGFPE,sig_fpe);
    error(bDANGER, "floating point error\n");
  }
}
/*--------------------------------------------------------------------------*/
static void setup_traps(void)
{
  signal(SIGFPE,sig_fpe);
  signal(SIGINT,sig_int);
  signal(SIGABRT,sig_abrt);
}
/*--------------------------------------------------------------------------*/
/* finish: clean up after a command
 * deallocates space, closes plot windows, resets i/o redirection, etc.
 * This is done separately for exception handling.
 * If a command aborts, clean-up is still done, leaving a consistent state.
 * //BUG// It is a function to call as a remnant of old C code.
 * Should be in a destructor, so it doesn't need to be explicitly called.
 */
static void finish(void)
{
  plclose();
  IO::mstdout.outreset();
}
/*--------------------------------------------------------------------------*/

static void do_getopt(int argc,  char * const * argv)
{
  int opt;
  int nsecs, tfnd=0;

  nsecs = 0;
  while ((opt = getopt(argc, argv, "a:c:b:i:qt:")) != -1) {
    switch (opt) {
      case 'q':
        OPT::quiet = true;
        break;
      case 't':
        nsecs = atoi(optarg);
        tfnd = 1;
        break;
      case 'a':
      case 'b':
      case 'c':
      case 'i':
        break;
      default: /* '?' */
        fprintf(stderr, "Usage: %s [-q] name\n", argv[0]); }
  }

//  printf("flags=%d; tfnd=%d; optind=%d, argc=%i\n", flags, tfnd, optind, argc);

  if (optind > argc) {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_FAILURE);
  }
  USE(tfnd); USE(nsecs);

}
/*--------------------------------------------------------------------------*/
static void process_cmd_line(int argc, char *const  *argv)
{
  for (int ii = 1;  ii < argc;  /*inside*/) {
    try {
      if (   !strcasecmp(argv[ii], "-v")  ){
        // FIXME. use git hash for development versions.
        cout << PACKAGE << " " << VERSION << endl;
        exit(1);
      } else if (   !strcasecmp(argv[ii], "-E")  
          || !strcasecmp(argv[ii], "-e") ) {
        ++ii;

        if (ii < argc) {
          string v = "";
          if (   !strcasecmp(argv[ii], "-E") )  
            v="verbose ";
            // dashier startet den OPT::language modus
	    CMD::command(string("expect ") + v + argv[ii++], &CARD_LIST::card_list);
        } else {
          incomplete();
        }
      }else if (strcasecmp(argv[ii], "-q") == 0) {
        ++ii;
          // doesnt do anything.
      }else if (strcasecmp(argv[ii], "-i") == 0) {
	++ii;
	if (ii < argc) {
	  CMD::command(std::string("include ") + argv[ii++], &CARD_LIST::card_list);
	}else{untested();
	}
      }else if (strcasecmp(argv[ii], "-c") == 0) { itested();
	++ii;
	if (ii < argc) { itested();
	  CS cmd(CS::_STRING, argv[ii++]); // command line
	  CMD::cmdproc(cmd, &CARD_LIST::card_list); 
	}else{untested();
	}
      }else if (strcasecmp(argv[ii], "-b") == 0) {
	try {
	  ++ii;
          // set languacge to spice (since we have defined acs as default.
          // this is a hack and might be a bug as well.
          CMD::command("spice", &CARD_LIST::card_list);
	  if (ii < argc) {
            // dashier startet den OPT::language modus
            trace2("-b...", OPT::language, argv[ii]);
	    CMD::command(std::string("< ") + argv[ii++], &CARD_LIST::card_list);
	  }else{untested();
	    CMD::command(std::string("< /dev/stdin"), &CARD_LIST::card_list);
	  }
	}catch (Exception& e) {
          error(bDANGER, e.message() + '\n');
          throw(Exception("error processing batch file"));
	  finish();
	}
	if (ii >= argc) {
	  CMD::command("end", &CARD_LIST::card_list);
	}else{untested();
	}
      }else if (strcasecmp(argv[ii], "-a") == 0) { itested();
	++ii;
	if (ii < argc) { itested();
	  CMD::command(std::string("attach ") + argv[ii++], &CARD_LIST::card_list);
	}else{untested();
	}
      }else{
	CMD::command(std::string("include ") + argv[ii++], &CARD_LIST::card_list);
      }
    }catch (Exception& e) {
      // hmmm
      throw(e);
    }
  }
}
/*--------------------------------------------------------------------------*/
int main(int argc, char * const * argv)
{
  CKT_BASE::_sim = new SIM_DATA;
  CKT_BASE::_probe_lists = new PROBE_LISTS;
  ENV::error = 0;

  // parse -v and -q _now_
  do_getopt(argc,argv);
  // sigsetjmp unneeded here (isnt it?)
  //
  // FIXME: use getopt
  //
  CMD::command("options lang=acs", &CARD_LIST::card_list);
  assert(OPT::language);
  read_startup_files();
  sign_on();

  {
    SET_RUN_MODE xx(rBATCH);
    trace0("batch mode");
    if (!sigsetjmp(env.p, true)) {
      try {
        trace0("... ");
	setup_traps();
        trace0("done traps");
	process_cmd_line(argc,argv);
        trace0("done cmdline  mode");
      }catch (Exception& e) {
        ENV::error++;
        std::cerr << e.message() << std::endl;
	finish();		/* error clean up (from longjmp()) */
	CMD::command("quit", &CARD_LIST::card_list);
	unreachable();
	exit(1);
      }
    }else{
      trace0("finish batch");
      finish();		/* error clean up (from longjmp()) */
      CMD::command("quit", &CARD_LIST::card_list);
      exit(0);
    }
  }
  {
    SET_RUN_MODE xx(rINTERACTIVE);
    trace0("interactive mode");
    CS cmd(CS::_STDIN);
    for (;;) {
      if (!sigsetjmp(env.p, true)) {
	try {
	  if (OPT::language) {
	    OPT::language->parse_top_item(cmd, &CARD_LIST::card_list);
	  }else{
	    CMD::cmdproc(cmd.get_line(I_PROMPT), &CARD_LIST::card_list);
	  }
	}catch (Exception_End_Of_Input& e) {
	  error(bDANGER, e.message() + '\n');
	  finish();
	  CMD::command("quit", &CARD_LIST::card_list);
	  exit(0);
	}catch (Exception& e) {
	  error(bDANGER, e.message() + '\n');
          ENV::error++;
	  finish();
	}
      }else{
	finish();		/* error clean up (from longjmp()) */
      }
    }
  }
  unreachable();
  return 1;
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:et:
