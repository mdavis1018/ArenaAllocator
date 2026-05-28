#pragma once

#include <mutex>
#include <cstdlib>
#include <cstddef>

/**
 * @brief Arena Template class
 * @details Manages memory in array like fashion. Useful
 * when max size of bytes is known at compile time. 
 * @param Class_t is a type
 * @param NumOfObjects_t is a std::size_t containing number of objects
 * in arena
 * 
*/
template <class Class_t, std::size_t NumOfObjects_t>
class Arena 
{
   private:
      /**
       * @brief Default ctr, meyers singleton (private)
      */
      Arena() : 
         mArenaPtr(static_cast<char*>(std::malloc(sizeof(Class_t) * NumOfObjects_t))),
         mCurrentPtr(mArenaPtr)
      {}

      /* Mutex so new and delete are thread safe */
      std::mutex mMutex;

      /* Ptr to start of arena block of memory*/
      char *mArenaPtr;

      /* Current ptr to track allocations */
      char *mCurrentPtr;


   public:
   
      /* Prevent Copy */
      Arena(const Arena&) = delete;

      /* Prevent Assignment */
      Arena& operator=(const Arena&) = delete;

      /**
       * @brief Destructor
       * @details Simply frees entire chunk, no subprocessing
      */
      ~Arena() 
      {
         std::free(mArenaPtr);
      }

      /**
       * @brief Singleton getter
       * @details Returns singleton reference
       * @return Arena 
      */
      static Arena &get()
      {
         static Arena tArenaSingleton;
         return tArenaSingleton;
      }

      /**
       * @brief Allocates a single object in arena
       * @details Returns address of mCurrentPtr then increments 
       * @return void pointer
      */
      void* allocateOne()
      {
         std::lock_guard<std::mutex> tLock(mMutex);
         void *tOut = mCurrentPtr;
         mCurrentPtr += sizeof(Class_t);
         return tOut;
      }

      /**
       * @brief Allocates an array of objects in arena
       * @details Returns address of mCurrentPrt then increments
       * @param aNumberOfObjects is a std::size_t
       * @return void pointer
      */
      void * allocateN(std::size_t aNumberOfObjects) 
      {
         std::lock_guard<std::mutex> tLock(mMutex);
         void *tOut = mCurrentPtr;
         mCurrentPtr += aNumberOfObjects * sizeof(Class_t);
         return tOut;
      }

      /**
       * @brief Empty method, Arena destructor cleans up
       * @note Override Class_t's delete allocater to call this
      */
      void deallocateOne(void *) noexcept 
      {
      }

      /**
       * @brief Empty method, Arena destructor cleans up
       * @note Override Class_t's delete[] allocater to call this
      */
      void deallocateN(void *) noexcept 
      {
      }

};    

