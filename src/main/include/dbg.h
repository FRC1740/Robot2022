#ifndef NEW_DMA_DBG
#define NEW_DMA_DBG

/* Usage
 *   After code defining DPRINTF, include this file
 *   set or clear the following
 *     DEBUG- clear for no debug prints at all
 *     DBGTHREAD - shows thread id for multithreaded applications
 *     DBGCALLER - shows the caller of each function (C++ can get messy)
 *   three or four letter defines- add at the beginning of each function in a module
 *   DBG- debug line, no string
 *   DBGz - debug line with string
 *   DBGST - any DEBUG statement (no terminating \n needed)
 */

#include <inttypes.h>
#include <string.h>
#define DEBUG
#ifdef DEBUG

#define noDBGTHREAD
#define noDBGCALLER

#ifdef DBGTHREAD  // ------------------------------
#include <pthread.h>
#define DBGFMTTHREAD "%p "
#define DBGBODYTHREAD pthread_self(),
#else
#define DBGFMTTHREAD ""
#define DBGBODYTHREAD
#endif  // DBGTHREAD ------------------------------

#ifdef DBGCALLER  // ------------------------------
#include <dlfcn.h>
#define DBGFMTCALLER "%-45s "
#define DBGDEFCALLER \
  void *retAddr = __builtin_extract_return_addr(__builtin_return_address(0)); \
  Dl_info d; \
  (void)dladdr(retAddr, &d);
#define DBGBODYCALLER (d.dli_sname)?d.dli_sname:"?"
#else
#define DBGFMTCALLER "%s"
#define DBGDEFCALLER
#define DBGBODYCALLER ""
#endif  // DBGCALLER ------------------------------

#define DBGLINEFILEFUNC "%5d %-23s %-32s "
#define DBGFMT DBGFMTTHREAD DBGLINEFILEFUNC DBGFMTCALLER ": "
#define DBGST(a,...) DBGSTn(a "\n", __VA_ARGS__)
#define DBGSTn(a,...) do {       \
  const char *FILENAME = strrchr(__FILE__, '/'); \
  DBGDEFCALLER                   \
  printf(                        \
  DBGFMT a,                      \
  DBGBODYTHREAD                  \
  __LINE__,                      \
  FILENAME?FILENAME+1:__FILE__,  \
  __FUNCTION__,                  \
  DBGBODYCALLER,                 \
  ##__VA_ARGS__); } while (0);

#define GK_DBGSTn(_a,...)                         \
do {                                              \
  char msg[256];                                  \
  snprintf(msg, sizeof(msg), _a, ##__VA_ARGS__);  \
  envise_print(msg);                              \
} while(0);

#define GK_DBGST(_a,...) GK_DBGSTn(_a "\n", ##__VA_ARGS__)
#define GK_DBGz(_a) GK_DBGST("%s", _a)
#define GKz GK_DBGz
#define GK GK_DBGz("");

// Use in envise_device_stubs.c
#define XENVISE_PRINT                                          \
envise_error xenvise_print(const char *s,                      \
          const char *xfile, int xline, const char *xfunction) \
{                                                              \
  char sbuf[400];                                              \
  const char *FILENAME = strrchr(xfile, '/');                  \
  snprintf(sbuf, sizeof(sbuf),                                 \
    DBGLINEFILEFUNC "| %s",                                    \
    xline, FILENAME?FILENAME+1:xfile, xfunction, s             \
  );                                                           \
  *((uint32_t *)ENVISE_PRINT_BLOCK_ADDRESS) = (uint32_t) sbuf; \
  return ENVISE_OK;                                            \
}

// Use in envise_device_stubs.c
#define STUB_XENVISE_PRINT                                     \
envise_error xenvise_print(const char *s,                      \
          const char *xfile, int xline, const char *xfunction) \
{                                                              \
  return table->xenvise_print(s, xfile, xline, xfunction);     \
}

// Use with this define and prototype:
// #define envise_print(_s) xenvise_print(_s, __FILE__, __LINE__, __FUNCTION__)
// envise_error xenvise_print(const char *s, const char *xfile, int xline, const char *xfunction);
                                                                                              

#ifdef MPI_DBG // ========================================================================================================================================================
#define TAGS \
  FN(ENVISE_COMMAND_TAG) \
  FN(ENVISE_RUN_DATA_SIZE) \
  FN(ENVISE_RUN_DATA) \
  FN(ENVISE_READ_META) \
  FN(ENVISE_WRITE_META) \
  FN(ENVISE_WRITE_DATA) \
  FN(ENVISE_INTERRUPT_DATA) \
  FN(ENVISE_LOCAL_DONE_TAG) \
  FN(ENVISE_DOORBELL_DATA) \

#define FN(_a) case _a: {snprintf(buf, 32, "%s", #_a); return buf;}
//static inline const char *tag_str(int tag, char *buf); // Prototype if the compiler warns
static inline const char *tag_str(int tag, char *buf) {
  switch (tag) {
    TAGS 
    default:
      { snprintf(buf, 32, "Numeric tag: %d", tag); return buf; }
  }
}
#undef FN

#define SHOW_MPI(source_or_dest, mpifunc)                    \
  do {                                                       \
    const char *FILENAME = strrchr(xfile, '/');              \
    char tag_buf[32];                                        \
    char sbuf[400];                                          \
    snprintf(sbuf, sizeof(sbuf),                             \
      DBGFMT                                                 \
      "%-11s count %2d datatype %-23s %-6s %d tag %s\n",     \
      xline, FILENAME?FILENAME+1:xfile, xfunc, "",           \
      mpifunc, count, dt_str,                                \
      #source_or_dest, source_or_dest, tag_str(tag, tag_buf) \
    );                                                       \
    printf("%s", sbuf);                                      \
  } while (0)

#define SHOW_MPI2 \
  do {                                                       \
    const char *FILENAME = strrchr(xfile, '/');              \
    char sbuf[400];                                          \
    snprintf(sbuf, sizeof(sbuf),                             \
      DBGFMT                                                 \
      "%-11s count %2d flag %2d rc %2d\n",                   \
      xline, FILENAME?FILENAME+1:xfile, xfunc, "",           \
      "MPI_Testall", count, myflag, rc                       \
    );                                                       \
    printf("%s", sbuf);                                      \
  } while (0)

static inline int my_MPI_Recv(int xline, const char *xfunc, const char *xfile, const char *dt_str,
  void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
  SHOW_MPI(source, "MPI_Recv ");
  return MPI_Recv(buf, count, datatype, source, tag, comm, status);
}

static inline int my_MPI_Irecv(int xline, const char *xfunc, const char *xfile, const char *dt_str,
  void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) {
  SHOW_MPI(source, "MPI_Irecv");
  return MPI_Irecv(buf, count, datatype, source, tag, comm, request);
}

static inline int my_MPI_Isend(int xline, const char *xfunc, const char *xfile, const char *dt_str,
  const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) {
  SHOW_MPI(dest, "MPI_Isend");
  return MPI_Isend(buf, count, datatype, dest, tag, comm, request);
}

static inline int my_MPI_Testall(int xline, const char *xfunc, const char *xfile,
  int count, MPI_Request array_of_requests[], int *flag, MPI_Status array_of_statuses[]) {
  int myflag;
  int rc = MPI_Testall(count, array_of_requests, &myflag, array_of_statuses);
  SHOW_MPI2;
  *flag = myflag;
  return rc;
}

#undef MPI_Recv
#undef MPI_Irecv
#undef MPI_Isend
#undef MPI_Testall
#define MPI_Recv(_a,_b,_dt,...)  my_MPI_Recv   (__LINE__, __FUNCTION__, __FILE__, #_dt, _a, _b, _dt, __VA_ARGS__)
#define MPI_Irecv(_a,_b,_dt,...) my_MPI_Irecv  (__LINE__, __FUNCTION__, __FILE__, #_dt, _a, _b, _dt, __VA_ARGS__)
#define MPI_Isend(_a,_b,_dt,...) my_MPI_Isend  (__LINE__, __FUNCTION__, __FILE__, #_dt, _a, _b, _dt, __VA_ARGS__)
#define MPI_Testall(_a,...)      my_MPI_Testall(__LINE__, __FUNCTION__, __FILE__, _a, __VA_ARGS__)
#endif // MPI_DBG ========================================================================================================================================================

#ifdef CPP_DBG
#include <sstream>
namespace std {
class Cbuf : public std::stringbuf
{
 public:
  void info(int xline, const char *xfunc, const char *xfile)
    { _line=xline; _func=xfunc; strncpy(_file, xfile, sizeof(_file)); }

  int dbg() {
    const char *FILENAME = strrchr(_file, '/');
    printf(DBGFMT "%s", _line, FILENAME?FILENAME+1:_file, _func.c_str(), "", _data.c_str());
    _data = ""; 
    return 0;
  }
 private:
  int _line;
  std::string _func;
  char _file[80];
  std::string _data;
 protected:
  virtual int_type overflow (int_type c) {
    if (c != EOF)
      _data.push_back(c);
    if (c == '\n')
      dbg();
    return c;
  }
};
std::Cbuf MyCbuf;
std::ostream MyCout(&MyCbuf);
} // namespace std 

#undef cout
#undef cerr
#define COUT MyCbuf.info(__LINE__, __FUNCTION__, __FILE__); std::MyCout
#define cout COUT
#define cerr COUT

#endif // CPP_DBG

#undef DPRINTF
#define DPRINTF(a,...) DBGSTn(a, ##__VA_ARGS__)

#else // DEBUG
#define DBGST(a,...)
#define DBGSTn(a,...)
#endif // DEBUG

#define DBG      DBGST("%s", "")
#define DBGz(a)  DBGST("%s", a)
#define DBGi(a)  DBGST("%s %u 0x%x", #a, (uint32_t) a, (uint32_t) a)
#define DBG64(a) DBGST("%s %" PRId64 " 0x%" PRIx64, #a, (uint64_t) a, (uint64_t) a)

// Ref: https://stackoverflow.com/questions/48045470/portably-detect-va-opt-support
#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),true,false,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)

#undef fprintf
#define fprintf(_b,_a,...)  DBGSTn(_a,##__VA_ARGS__)  // make source use DBGST
#define dprintf             DPRINTF  // since we already use printf, need to make source use DBGST
#define xprintf(_a,...)     // Remove wordy statements
#define xfprintf(_a,...)    // Remove wordy statements

#undef LOG
#define LOG(_b,_a,...) DBGSTn("%-11s " _a,#_b,##__VA_ARGS__)

#ifdef CMEM_PRINT_USE // -------------------------------------------------------
#define CMEM_STR_COUNT 200
#define CMEM_STR_LEN 256

typedef struct __attribute__((aligned(32))) cmem_print_t {
  uint32_t index;
  uint32_t pad0[7];
  uint32_t len;
  uint32_t pad1[7];
  uint32_t count;
  uint32_t pad2[7];
  char str[CMEM_STR_COUNT][CMEM_STR_LEN];
} cmem_print_t __attribute__((aligned(32))); 

void put_device_str(const char *s);

#undef DBGSTn
#undef GK_DBGSTn
#undef GK_DBG
#undef DPRINTF
#undef serr
#undef sinfo
#undef nuttx_envise_print

#define DBGSTn GK_DBGSTn
#define DPRINTF GK_DBGSTn
#define serr GK_DBGSTn
#define sinfo GK_DBGSTn
#define nuttx_envise_print(_a) GK_DBGSTn("%s", _a)

#define GK_DBGSTn DEVICE_DBGSTn
#define GK_DBG DEVICE_DBGSTn("%s\n","");

#define DEVICE_DBGSTn(a,...) do { \
  char sbuf[CMEM_STR_LEN];       \
  const char *FILENAME = strrchr(__FILE__, '/'); \
  DBGDEFCALLER                   \
  snprintf(sbuf, sizeof(sbuf),   \
  DBGFMT a,                      \
  DBGBODYTHREAD                  \
  __LINE__,                      \
  FILENAME?FILENAME+1:__FILE__,  \
  __FUNCTION__,                  \
  DBGBODYCALLER,                 \
  ##__VA_ARGS__);                \
  put_device_str(sbuf);          \
} while (0);

#endif // CMEM_PRINT_USE --------------------------------------------------------

#ifdef CMEM_PRINT_VAR // -------------------------------------------------------
cmem_print_t stack_cmem_print;
cmem_print_t *cmem_print __attribute__((aligned(32)));
volatile uint32_t cmem_print_init;
volatile uint32_t cmem_print_ready;
sem_t cmem_print_sem;

void put_device_str(const char *s) {
#ifdef CONFIG_ARCH_CHIP_E76MC_NATIVE
  if (cmem_print_init != 314159) {
    cmem_print_init = 314159;
    (void) nxsem_init(&cmem_print_sem, 0, 0);
    stack_cmem_print.index = 0;
    stack_cmem_print.len = CMEM_STR_LEN;
    stack_cmem_print.count = CMEM_STR_COUNT;
    cmem_print = &stack_cmem_print;
    cmem_print_ready = 271828;
    nxsem_post(&cmem_print_sem);
  }
  else {
    while (cmem_print_ready != 271828) {
    }
  }
  nxsem_wait(&cmem_print_sem);
  uint32_t i = cmem_print->index;
  if (memchr(s, '\n', CMEM_STR_LEN) == NULL) {
    snprintf(cmem_print->str[i], sizeof(cmem_print->str[i]) - 1, "%s\n", s);
  }
  else {
    snprintf(cmem_print->str[i], sizeof(cmem_print->str[i]) - 1, "%s", s);
  }
  i++;
  if (i >= CMEM_STR_COUNT) i = 0;
  cmem_print->index = i;
  nxsem_post(&cmem_print_sem);
#else
  printf("%s", s);
#endif // ENVISE_NATIVE
}

// Put this in initialization code so compiler does not optimize out
// cmem_print->len = CMEM_STR_LEN;

#endif // CMEM_PRINT_VAR -------------------------------------------------------

#ifdef CMEM_PRINT_HOST //-------------------------------------------------------

// prototypes
uint64_t envise_get_symbol(envise_handle *handle, const char *symbol, int namespace);
void read_cmem_wrapper(envise_handle *handle, void *dest, size_t size, uint64_t device_address);

uint32_t cmem_print_ptr = 0;
uint32_t cmem_print_str = 0;
uint32_t cmem_print_local_index = 0;
uint32_t cmem_print_remote_index = 0;
uint32_t cmem_print_len = 0;
uint32_t cmem_print_count = 0;

void put_device_str(const char *s)
{
  printf("%s", s);
}

typedef union staging_t {
  uint32_t words[8];
} staging_t __attribute__((aligned(64)));
staging_t staging __attribute__((aligned(64)));

#include <semaphore.h>
sem_t print_sem;

void setup_cmem_printer(envise_handle *handle)
{
  if ((cmem_print_len != 0) && (cmem_print_count != 0) && (cmem_print_ptr != 0)) { return; }
  // Get pointer address
  uint32_t cmem_print_addr = envise_get_symbol(handle, "cmem_print", ENVISE_OS_NAMESPACE);
  //LOG(LOG_INFO, "cmem_print_addr 0x%x\n", cmem_print_addr);

  read_cmem_wrapper(handle, &staging, sizeof(staging), (uint64_t) cmem_print_addr);
  cmem_print_ptr = staging.words[0];
  //LOG(LOG_INFO, "cmem_print_ptr 0x%x\n", cmem_print_ptr);

  if (cmem_print_ptr != 0) {
    DBGz("......................................................................................................... ");
  
    cmem_print_local_index = 0;
    // Retrieve data at pointer
    read_cmem_wrapper(handle, &staging, sizeof(staging), (uint64_t) cmem_print_ptr + 32);
    cmem_print_len = staging.words[0];
    read_cmem_wrapper(handle, &staging, sizeof(staging), (uint64_t) cmem_print_ptr + 64);
    cmem_print_count = staging.words[0];
    cmem_print_str = cmem_print_ptr + 3 * 32;
    LOG(LOG_INFO, "-> cmem_print str is 0x%x len %d count %d\n", (uint32_t) (cmem_print_str & 0xffffffff), cmem_print_len, cmem_print_count);

    if ((cmem_print_len == 0) || (cmem_print_count == 0)) { cmem_print_ptr = 0; }
  }
  (void) sem_init(&print_sem, 0, 1);
}

int update_cmem_print_remote_index()
{
  int rc = 0;
  setup_cmem_printer(device_handle); 
  if ((cmem_print_len == 0) || (cmem_print_count == 0) || (cmem_print_ptr == 0)) return rc;

  rc = 1;
  read_cmem_wrapper(device_handle, &staging, sizeof(staging), (uint64_t) cmem_print_ptr);
  cmem_print_remote_index = staging.words[0];
  return rc;
}

void get_cmem_print_str(char *s, uint32_t index)
{
  read_cmem_wrapper(device_handle, s, cmem_print_len, (uint64_t) cmem_print_str + index * cmem_print_len);
}

void show_enabled_ints();
void device_cmem_strings()
{
  char s[257] __attribute__((aligned(32)));
  if (update_cmem_print_remote_index()) {
    sem_wait(&print_sem);
    while (cmem_print_local_index != cmem_print_remote_index) {
      get_cmem_print_str(s, cmem_print_local_index);
      printf("Device: %s", s);
      cmem_print_local_index++;
      if (cmem_print_local_index > cmem_print_count) cmem_print_local_index = 0;
    }
    sem_post(&print_sem);
#ifdef INT_CSR_DBG_HOST
    show_enabled_ints();
#endif
  }
}

#include "poll.h"
void check_for_interrupt(int fd) 
{
  struct pollfd fds;
  fds.fd = fd; 
  fds.events = POLLIN | POLLRDBAND;
  int msecs = 100; 
  device_cmem_strings();
  while (1) {
    int ret = poll(&fds, 1, msecs); 
    if (ret == 0) { 
      // Call timed out 
      device_cmem_strings();
    } else {
      break;  
    }   
  }
}

// This call goes into the library at initialization tinme (setup_queues)
// setup_cmem_printer(handle);

// This call goes into the library inside a polling loop (envise_wait)
// device_cmem_strings();

// This call goes into the library before a (blocking) read (wait_for_interrupt)
// check_for_interrupt(fd);

#endif // CMEM_PRINT_HOST ------------------------------------------------------


#ifdef INT_CSR_DBG_HOST // -----------------------------------------------------
#undef MCTL_GW_ADDR_OFFSET
#undef MCTL_GW_REQ_DATA_OFFSET
#undef MCTL_GW_REQ_OFFSET
#undef MCTL_GW_RSP_DATA_OFFSET
#define MCTL_GW_ADDR_OFFSET        0x200
#define MCTL_GW_REQ_DATA_OFFSET    0x208
#define MCTL_GW_REQ_OFFSET         0x204
#define MCTL_GW_RSP_DATA_OFFSET    0x20c

#ifndef PCIE0_CSR_BASE_ADDRESS
#define PCIE0_CSR_BASE_ADDRESS     0x44000000
#endif

uint32_t read_with_mctl_gateway(uint32_t addr, uint32_t *result)
{
  int call_result = 0;
  addr += PCIE0_CSR_BASE_ADDRESS;
  call_result = read_with_gateway(MCTL_GW_ADDR_OFFSET, MCTL_GW_REQ_DATA_OFFSET, MCTL_GW_REQ_OFFSET, MCTL_GW_RSP_DATA_OFFSET, addr, result);
  return call_result;
}
#endif // INT_CSR_DBG_HOST -----------------------------------------------------


#ifdef INT_CSR_DBG // ----------------------------------------------------------
typedef struct envise_int_csr_t {
  uint32_t _int : 1;
  uint32_t _int_en : 1;
  uint32_t _int_global_en : 1;
  uint32_t _int_sel : 5;
  uint32_t _int_hart_sel : 2;
} envise_int_csr_t;

typedef struct envise_int_csr_accessor_t {
  envise_int_csr_t reg;
  uint32_t word;
} envise_int_csr_accessor_t;

int int_csr_str(envise_int_csr_t *csr, char *s)
{
  sprintf(s, "%c %x %x %2d %c",
    csr->_int ? '!' : '-',
    csr->_int_en,
    csr->_int_global_en,
    csr->_int_sel,
    csr->_int_global_en ? '-' : csr->_int_hart_sel + '0'
  );
  return ((csr->_int_en == 1) || (csr->_int == 1));
}

uint32_t get_interrupt_status(uint32_t ctl_cfg)
{
  uint32_t rc = 0;
  read_with_mctl_gateway(ctl_cfg, &rc);
  return rc;
}

// TODO: use jupiter headers and eliminate the constants
#define CSRS \
  CFN(MCTL_MAP_PCIE0_PCIE_LNK_DN_CTL_ADDR,     0x24) \
  CFN(MCTL_MAP_PCIE1_PCIE_LNK_DN_CTL_ADDR,     0x28) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_0_ADDR,     0x30) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_1_ADDR,     0x34) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_2_ADDR,     0x38) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_3_ADDR,     0x3c) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_4_ADDR,     0x40) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_5_ADDR,     0x44) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_6_ADDR,     0x48) \
  CFN(MCTL_MAP_PCIE0_EDMA_DONE_CTL_7_ADDR,     0x4c) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_0_ADDR,     0x50) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_1_ADDR,     0x54) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_2_ADDR,     0x58) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_3_ADDR,     0x5c) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_4_ADDR,     0x60) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_5_ADDR,     0x64) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_6_ADDR,     0x68) \
  CFN(MCTL_MAP_PCIE1_EDMA_DONE_CTL_7_ADDR,     0x6c) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_0_ADDR,      0x70) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_1_ADDR,      0x74) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_2_ADDR,      0x78) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_3_ADDR,      0x7c) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_4_ADDR,      0x80) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_5_ADDR,      0x84) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_6_ADDR,      0x88) \
  CFN(MCTL_MAP_PCIE0_EDMA_ERR_CTL_7_ADDR,      0x8c) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_0_ADDR,      0x90) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_1_ADDR,      0x94) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_2_ADDR,      0x98) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_3_ADDR,      0x9c) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_4_ADDR,      0xa0) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_5_ADDR,      0xa4) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_6_ADDR,      0xa8) \
  CFN(MCTL_MAP_PCIE1_EDMA_ERR_CTL_7_ADDR,      0xac) \
  CFN(MCTL_MAP_PCIE0_EDMA_APB_RD_ERR_CTL_ADDR, 0xb0) \
  CFN(MCTL_MAP_PCIE1_EDMA_APB_RD_ERR_CTL_ADDR, 0xb4) \
  CFN(MCTL_MAP_PCIE0_EDMA_APB_WR_ERR_CTL_ADDR, 0xb8) \
  CFN(MCTL_MAP_PCIE1_EDMA_APB_WR_ERR_CTL_ADDR, 0xbc) \
  CFN(MCTL_MAP_IDMA_DONE_INT_CFG_ADDR,         0x4108) \
  CFN(MCTL_MAP_IDMA_BP_INT_CFG_ADDR,           0x410c) \
  CFN(MCTL_MAP_IDMA_HWE_INT_CFG_ADDR,          0x4110) \

#define CFN(_a, _b) { \
  envise_int_csr_accessor_t u; \
  u.word = get_interrupt_status(_b); \
  char s[100]; \
  int rc = int_csr_str(&u.reg, s); \
  if (rc >= 0) { \
    DBGSTn("%-40s 0x%04x %s\n", #_a, _b, s); \
  } \
}

void show_enabled_ints(void) { CSRS }

#endif // INT_CSR_DBG ----------------------------------------------------------

#ifdef HEX_DUMP // -------------------------------------------------------------
#include <ctype.h>
typedef struct hex_dump_format {
    void *base;
    char *format[4];
    size_t every;
} hex_dump_format_t;

#define CAT(a) strncat(line, a, sizeof(line) - strlen(line) + 1)

void
hex_dump(void *buf, size_t size, size_t per_line, hex_dump_format_t *format)
{
  unsigned char *b = (unsigned char *) buf;
  unsigned char *base = b;
  const char *f[4] = {"%4d: ", "%02x ", " ", "  " };
  size_t s = 8;
  char line[133];
  char *a, asc[133];
  char temp[20];
  int i, j, k;

  /* Code to handle format structure */
  if (format)
  {  
    for (i = 0; i < 4; i++)
      f[i] = format->format[i];
    base = (unsigned char *) format->base;
    s = format->every;
  }  

  /* Enhancement- handle little endian case */
  line[0] = '\0';
  memset(asc, 0, sizeof(asc));
  a = asc;
  for (i = 0; i < size; i++)
  {  
    if (!(i % per_line))
      sprintf(line, f[0], ((size_t) &b[i] - (size_t) base));
    a[0] = isprint(b[i]) ? b[i] : '.';
    a++;
    sprintf(temp, f[1], b[i]);
    CAT(temp);
    if ((s) && (((i % per_line) % s) == s - 1)) 
      CAT(f[2]);
    if (((i % per_line) == per_line - 1) || (i == size - 1)) 
    {  
      if ((i == size - 1) && (size % per_line))
        for (j = i + 1; j < (((size + per_line) / per_line) * per_line); j++)
        {  
          for (k = 0; k < strlen(temp); k++)
            CAT(" "); 
          if ((s) && (((j % per_line) % s) == s - 1)) 
            CAT(f[2]);
        }  
      CAT(f[3]);
      CAT(asc);
      DBGz(line);
      line[0] = '\0';
      memset(asc, 0, sizeof(asc));
      a = asc;
    }  
  }  
}
// usage:
//   hex_dump(pointer, size, 16, NULL); // bytewise
//   hex_dump_format_t f = {(void *) ((uintptr_t) (p) & 0xFFFFFFFF00000000), {"%8lx: ", "%02x", " ", "  " }, 0, };
//   hex_dump(pointer, size, 4, &f ); // dwords (but low byte first)
#endif // HEX_DUMP  -----------------------------------------------------------

#endif // NEW_DMA_DBG

