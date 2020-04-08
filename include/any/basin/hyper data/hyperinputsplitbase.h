/*!
 * The AnyBase of PetroCOVERY Solution is a collection of native C++ classes that implement the fundamental 
 * algorithms & operations required to satisfy COMMON DEMANDS of other packages.
 *
 * Copyright (C) 2015 XIUJIE SHENG
 *
 * This library isn't a free software, so you cann't take the source code without author's permit.
 * Of course, there is NO ANY WARRANTY that this library will not harm your computer or ongoing 
 * business if you illegally got it. 
 *
 * NOTE: 
 * AUTHOR WOULD ALWAYS RESERVE LEGAL RIGHT TO PROTECT WHAT HE HAVE DONE ACCORDING TO
 * LOCAL OR INTERNATIONAL COPYRIGHT OR RELATIVE LAW(S).
 *
 * For more information, contact:
 *
 * China University of Geoseciences(Wuhan)
 * Resource Faculty
 *
 * Xiujie Sheng
 * herman.sheng@gmail.com
 */
#ifndef __ANYBASIN_HYPER_DATA_INPUT_SPLIT_BASE__H__
#define __ANYBASIN_HYPER_DATA_INPUT_SPLIT_BASE__H__

#include "hyperstream.h"
#include "hyperfilesystem.h"

//
namespace AnyBasin
{
	/*! \brief class to construct input split from multiple files */
	class HyperInputSplitBase : public HyperInputSplit 
	{
	 public:
		/*!
		* \brief helper struct to hold chunk data
		*  with internal pointer to move along the record
		*/
		struct Chunk 
		{
			char *begin;
			char *end;
			std::vector<size_t> data;
			explicit Chunk(size_t buffer_size)
				: begin(NULL), end(NULL),
					data(buffer_size + 1) {}
			// load chunk from split
			bool Load(HyperInputSplitBase *split, size_t buffer_size);
		};
		// 16 MB
		static const size_t kBufferSize = 2UL << 20UL;
		// destructor
		virtual ~HyperInputSplitBase(void);
		// implement BeforeFirst
		virtual void BeforeFirst(void);
		virtual void HintChunkSize(size_t chunk_size) 
		{
			buffer_size_ = std::max(chunk_size / sizeof(size_t), buffer_size_);
		}
		virtual size_t GetTotalSize(void) 
		{
			return file_offset_.back();
		}
		// implement next record
		virtual bool NextRecord(Blob *out_rec) 
		{
			while(!ExtractNextRecord(out_rec, &tmp_chunk_)) 
			{
				if (!tmp_chunk_.Load(this, buffer_size_)) return false;
			}
			return true;
		}
		// implement next chunk
		virtual bool NextChunk(Blob *out_chunk) 
		{	
			while (!ExtractNextChunk(out_chunk, &tmp_chunk_)) 
			{
				if (!tmp_chunk_.Load(this, buffer_size_)) return false;
			}
			return true;
		}
		// implement ResetPartition.
		virtual void ResetPartition(unsigned rank, unsigned nsplit);
		/*!
		* \brief read a chunk of data into buf
		*   the data can span multiple records,
		*   but cannot contain partial records
		*
		* \param buf the memory region of the buffer,
		*        should be properly aligned to 64 bits
		* \param size the maximum size of memory,
		*   after the function returns, it stores the size of the chunk
		* \return whether end of file was reached
		*/
		bool ReadChunk(void *buf, size_t *size);
		/*!
		* \brief extract next chunk from the chunk
		* \param out_chunk the output record
		* \param chunk the chunk information
		* \return true if non-empty record is extracted
		*    false if the chunk is already finishes its life
		*/
		bool ExtractNextChunk(Blob *out_rchunk, Chunk *chunk);
		/*!
		* \brief extract next record from the chunk
		* \param out_rec the output record
		* \param chunk the chunk information
		* \return true if non-empty record is extracted
		*    false if the chunk is already finishes its life
		*/
		virtual bool ExtractNextRecord(Blob *out_rec, Chunk *chunk) = 0;

	protected:
		// constructor
		HyperInputSplitBase()
			: fs_(NULL),
			align_bytes_(8),
			tmp_chunk_(kBufferSize),
			buffer_size_(kBufferSize) {}
		/*!
		* \brief intialize the base before doing anything
		* \param fs the filesystem ptr
		* \param uri the uri of the files
		* \param rank the rank of the split
		* \param nsplit number of splits
		* \param align_bytes the head split must be multiple of align_bytes
		*   this also checks if file size are multiple of align_bytes
		*/
		void Init(HyperFileSystem *fs,
				const char *uri,
				size_t align_bytes);
		// to be implemented by child class
		/*!
		* \brief seek to the beginning of the first record
		*        in current file pointer
		* \return how many bytes we read past
		*/
		virtual size_t SeekRecordBegin(HyperStream *fi) = 0;
		/*!
		* \brief find the last occurance of record header
		* \param begin beginning of the buffer
		* \param end end of the buffer
		* \return the pointer between [begin, end] indicating the
		*         last record head
		*/
		virtual const char*
		FindLastRecordBegin(const char *begin, const char *end) = 0;

	private:
		/*! \brief FileSystem */
		HyperFileSystem *filesys_;
		/*! \brief information about files */
		std::vector<FileInfo> files_;
		/*! \brief current input stream */
		HyperSeekStream *fs_;
		/*! \brief bytes to be aligned */
		size_t align_bytes_;
		/*! \brief file pointer of which file to read on */
		size_t file_ptr_;
		/*! \brief file pointer where the end of file lies */
		size_t file_ptr_end_;
		/*! \brief get the current offset */
		size_t offset_curr_;
		/*! \brief beginning of offset */
		size_t offset_begin_;
		/*! \brief end of the offset */
		size_t offset_end_;
		/*! \brief temporal chunk */
		Chunk tmp_chunk_;
		/*! \brief buffer size */
		size_t buffer_size_;
		/*! \brief byte-offset of each file */
		std::vector<size_t> file_offset_;
		/*! \brief internal overflow buffer */
		std::string overflow_;
		/*! \brief initialize information in files */
		void InitInputFileInfo(const std::string& uri);
		/*! \brief strip continous chars in the end of str */
		std::string StripEnd(std::string str, char ch);
		/*! \brief same as stream.Read */
		size_t Read(void *ptr, size_t size);
	};

}
#endif
