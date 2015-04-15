/*
 * List.h
 *
 *      Author: bill
 */

#ifndef LIST_H_
#define LIST_H_

template <typename T>

class List
{
public:
	List(const uint16_t capacity);
	void clear();
	uint16_t add(const T item);
	void remove(const uint16_t index);
	T& item(const uint16_t index) const;
	uint16_t count() const { return m_count; }
	uint16_t size() const { return m_size; }


protected:
	void _rebuildData(const uint16_t size);

	uint16_t m_count;
	uint16_t m_size;
	uint16_t m_capacity;
	T *m_data;
};


template <typename T>
List<T>::List(const uint16_t capacity)
{
	m_capacity = capacity;
	m_size = 0;
	m_count = 0;
	m_data = NULL;
}

template <typename T>
void List<T>::clear()
{
	free(m_data);
	m_data = NULL;
	m_size = 0;
	m_count = 0;
}

template <typename T>
uint16_t List<T>::add(const T item)
{
	if ( m_data == NULL || m_size == 0) {
		_rebuildData(m_capacity);
	}
	if ( m_count + 1 >= m_size) {
		_rebuildData(m_count + m_capacity);
	}
	memcpy(&m_data[m_count], &item, sizeof(T));
	m_count ++;
	return m_count - 1;
}

template <typename T>
void List<T>::remove(const uint16_t index)
{
	if ( index < m_count && m_count > 0) {
		uint16_t a;
		for (a = index + 1; a < m_count ; a ++ ) {
			memcpy(&m_data[a - 1] , &m_data[a], sizeof(T));
		}
		m_count --;
	}
}

template <typename T>
T& List<T>::item(const uint16_t index) const
{
	if ( index < m_count ) {
		return m_data[index];
	}
	T empty;
	memset(&empty, 0, sizeof(T));
	return empty;
}


template <typename T>
void List<T>::_rebuildData(uint16_t size)
{
	T *newData = (T *) malloc(sizeof(T) * size);
	memset(newData, 0, sizeof(T) * size);

	if ( m_data ) {
		memcpy(newData, m_data, sizeof(T) * m_size);
		free(m_data);
	}

	m_data = newData;
	m_size = size;
}



#endif /* LIST_H_ */
